#include <iostream>
#include <time.h>// 시간 측정 위해서
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <sstream>
#include <vector>

using namespace std;

int flag = 0;

cv::Mat input_im, dst;
clock_t start_time, end_time;

void Average(int kernelsize, void *userData);

string type2str(int type);

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim))
		elems.push_back(item);
	return elems;
}

std::vector<std::string> split(const std::string &s, char delim)
{
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

void Average(int kernelsize, void *userData)
{
	string &win_name = *(static_cast<string*>(userData));
	start_time = clock();
	int value = kernelsize;
	int h = input_im.rows;
	int w = input_im.cols;
	dst = cv::Mat(h, w, CV_8UC1);
	cout << "value:" << value << endl;
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


	if (flag == 1)
	{
		cv::blur(input_im, dst, cv::Size(value, value));
	}
	else if (flag == 2)
	{
		int check = int(value / 2);

		for (int row = 0; row < input_im.rows; row++)
		{
			for (int col = 0; col < input_im.cols; col++)
			{
				int mean = 0;
				for (int k_row = check; k_row >= -check; k_row--)
				{
					for (int k_col = check; k_col >= -check; k_col--)
					{
						if ((row - k_row < 0) || (col - k_col < 0) || (row - k_row >= input_im.rows) || (col - k_col >= input_im.cols))
						{
							mean += 0;
						}
						else
						{
							mean += input_im.at<uchar>(row - k_row, col - k_col);
						}
					}
				}
				int new_mean = 0;
				new_mean = (mean / (value*value));
				dst.at<uchar>(row, col) = new_mean;
			}
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

int main(int argc, char *argv[])
{

	string line;
	string adrs;

	getline(cin, line);
	line.append(" 0");
	vector<string> x(2, "");
	x = split(line, ' ');

	adrs = x[0];

	if (x[1] == "0")
	{
		cout << "ERROR : No flag" << endl;
		cout << "Execute as a default flag : 1" << endl;
		flag = 1;
	}
	else
	{
		flag = atoi(x[1].c_str());
		if ((flag != 1) && (flag != 2))
		{
			cout << "Flag have to be 1 or 2" << endl;
			cout << "Execute as a default flag : 1" << endl;
			flag = 1;
		}
	}

	input_im = cv::imread(adrs, CV_LOAD_IMAGE_GRAYSCALE);



	if (input_im.empty())
	{
		cout << "File open Error!" << endl;
		return -1;
	}
	cout << "Image size :" << input_im.size() << ", Type:" << type2str(input_im.type()) << endl;

	string window_name = "Average Filtering Window";
	cv::namedWindow(window_name);

	int start_value = 0;
	int max_value = 15;

	cv::createTrackbar("KernelSize", window_name, &start_value, max_value, Average, static_cast<void*>(&window_name));

	imshow(window_name, input_im);
	cv::waitKey(0);

	return 0;
}