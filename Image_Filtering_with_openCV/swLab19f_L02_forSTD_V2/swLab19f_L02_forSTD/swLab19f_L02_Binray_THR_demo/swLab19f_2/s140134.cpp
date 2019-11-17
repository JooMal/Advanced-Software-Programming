#include <iostream>
#include <time.h>// 시간 측정 위해서
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;
using namespace cv;

Mat input_im, dst;
clock_t start_time, end_time;

void Moving_Average(int kernelsize, void *userData);

string type2str(int type);

void Moving_Average(int kernelsize, void *userData)
{
	string &win_name = *(static_cast<string*>(userData));
	start_time = clock();
	int value = kernelsize;
	int h = input_im.rows;
	int w = input_im.cols;
	dst = Mat(h, w, CV_8UC1);
	cout << "value:" << value << endl;
	cout << "start!!!" << endl;
	// 여기서 뭔가를 한다



	if ((0 <= value) && (value <= 2))
	{
		value = 3;
	}
	else if ((3 <= value) && (value < 5))
	{
		value = 3;
	}
	else if ((5 <= value) && (value < 7))
	{
		value = 5;
	}
	else if ((value <= 7) && (value < 9))
	{
		value = 7;
	}
	else if ((value <= 9) && (value < 11))
	{
		value = 9;
	}
	else if ((value <= 11) && (value < 13))
	{
		value = 11;
	}
	else if ((value <= 13) && (value < 15))
	{
		value = 13;
	}
	else
	{
		value = 15;
	}


	//Moving Average 구현하기


	queue <int> q;

	int check = int(value / 2);
	int sum = 0;
	
	cout << "---start---" << endl;

	for (int row = 0; row < input_im.rows; row++)
	{
		for (int col = 0; col < input_im.cols; col++)
		{
			for (int k_col = -check; k_col < input_im.cols+check; k_col++)
			{
				int mean = 0;
				for (int k_row = check; k_row >= -check; k_row--)
				{
					if ((row - k_row < 0) || (k_col < 0) || (row - k_row >= input_im.rows) || (k_col >= input_im.cols))
					{
						mean += 0;
					}
					else
					{
						mean += input_im.at<uchar>(row - k_row, k_col);
					}
				}
				sum += mean;
				cout << "now_mean: " << mean << endl;
				q.push(mean);
			}
			cout << "now_sum: " << sum << endl;
			dst.at<uchar>(row, col) = sum;
			sum -= q.front();
			q.pop();
		}
	}



	end_time = clock();

	cout << "value : " << value << ", Exec Time : " << (double)(end_time - start_time) << " (msec)" << endl;



	imshow(win_name, dst);

}



string type2str(int type) {

	// https://stackoverflow.com/questions/10167534/how-to-find-out-what-type-of-a-mat-object-is-with-mattype-in-opencv

	string r;



	uchar depth = type & CV_MAT_DEPTH_MASK;

	uchar chans = 1 + (type >> CV_CN_SHIFT);



	switch (depth) {

	case CV_8U:  r = "8U"; break;

	case CV_8S:  r = "8S"; break;

	case CV_16U: r = "16U"; break;

	case CV_16S: r = "16S"; break;

	case CV_32S: r = "32S"; break;

	case CV_32F: r = "32F"; break;

	case CV_64F: r = "64F"; break;

	default:     r = "User"; break;

	}



	r += "C";

	r += (chans + '0');



	return r;

}



//argc = 들어온 입력 갯수, argv = 입력이 white space로 구분되어 하나씩 들어간다

int main(int argc, char *argv[])
{
	cout << "START" << endl;

	if (argc != 3)

	{

		cout << "[프로그램 사용법]" << endl;

		cout << "명령문 : s140134HW01.exe imageFile kernelSize<ent>" << endl;

	}


	input_im = cv::imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);


	if (input_im.empty())

	{

		cout << "File open Error!" << endl;

		return -1;

	}

	cout << "Filename = " << argv[1];

	cout << "Image size :" << input_im.size() << ", Type:" << type2str(input_im.type()) << endl;

	cout << "Kernel Size : " << argv[2];

	string window_name = "Average Filtering Window";

	cv::namedWindow(window_name);



	int start_value = 3;

	int max_value = 15;



	cv::createTrackbar("KernelSize", window_name, &start_value, max_value, Moving_Average, static_cast<void*>(&window_name));



	imshow(window_name, input_im);

	cv::waitKey(0);



	return 0;

}