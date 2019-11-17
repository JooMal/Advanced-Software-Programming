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

void Moving_Average(int kernelsize);

string type2str(int type);

void Moving_Average(int kernelsize)
{
	string window_name = "Average Filtering Window";
	
	start_time = clock();
	int value = kernelsize;
	int h = input_im.rows;
	int w = input_im.cols;
	dst = Mat(h, w, CV_8UC1);


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

	
	int check = int(value / 2);
	int sum = 0;


	for (int row = 0; row < input_im.rows; row++) 
	{
		int kernel_sum = 0;
		queue <int> q;
		for (int col = -check; col < input_im.cols+check; col++) 
		{
			int row_sum = 0;
			for (int k_row = -check+row; k_row < row+check; k_row++)
			{
				if ((col < 0) || (col+check > input_im.cols) || (k_row < 0) || (k_row+check > input_im.rows))
				{
					row_sum += 0;
				}
				else
				{
					row_sum += input_im.at<uchar>(k_row, col); 
				}

			} 
			q.push(row_sum);
			kernel_sum += row_sum;

			if (q.size() == value)
			{
				dst.at<uchar>(row, col-check) = (kernel_sum / (value*value));
				kernel_sum -= q.front();
				q.pop();
			}
			
		}
	}


	end_time = clock();
	cout << "Kernel Size : " << value << ", Exec Time : " << (double)(end_time - start_time) << " (msec)" << endl;

	imshow(window_name, dst);

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
	//cout << "START" << endl;

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

	string window_name = "Average Filtering Window";

	cv::namedWindow(window_name);

	int size = atoi(argv[2]);
	Moving_Average(size);


	cv::waitKey(0);



	return 0;

}