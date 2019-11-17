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

void Median(int kernelsize, void *userData);

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

void Median(int kernelsize, void *userData)
{
	string &win_name = *(static_cast<string*>(userData));
	start_time = clock();
	int value = kernelsize;

	if ((0 <= value) && (value <= 2))
	{
		value = 1;
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

	cv::medianBlur(input_im, dst, value);

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
	vector<string> x(2, " ");
	x = split(line, ' ');
	if (x[1] != "0")
	{
		cout << "Error: There is flag!" << endl;
		cout << "execute with default value" << endl;
	}

	adrs = x[0];

	input_im = cv::imread(adrs, CV_LOAD_IMAGE_GRAYSCALE);
	if (input_im.empty())
	{
		cout << "File open Error!" << endl;
		return -1;
	}
	cout << "Image size :" << input_im.size() << ", Type:" << type2str(input_im.type()) << endl;

	string window_name = "Median Filtering Window";
	cv::namedWindow(window_name);

	//Create track bar to change kernel size
	int start_value = 0;
	int max_value = 15;

	//start_value를 value로 사용하면 된다. 근데 value로는 홀수로 써서, 바꿔줘야함
	//cv::createTrackbar("ThresholdValue", window_name, &start_value, max_value, binaryThresholding_opencvCommand, static_cast<void*>(&window_name));
	cv::createTrackbar("KernelSize", window_name, &start_value, max_value, Median, static_cast<void*>(&window_name));

	imshow(window_name, input_im);
	cv::waitKey(0);

	return 0;
}