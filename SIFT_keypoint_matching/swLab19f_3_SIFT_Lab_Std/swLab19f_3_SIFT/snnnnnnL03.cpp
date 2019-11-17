#include "SIFT.h"
#define DIST_RATIO_THR 0.49
#include <queue>


void customGaussianBlur(const Mat &src, Mat &dst, double sigma) {

	////////////////////////////////////////////////////////////

	// 가우시안 커널을 생성해 이미지에 적용하는 함수

	// 커널의 크기는 2*(4*sigma)+1 (소수점은 올림 또는 반올림으로 처리한다)

	// 가우시안 커널은 float형의 값을 가짐

	// 가우시안 커널은 커널 값 계산 후 전체의 총합으로 나눠서 0~1사이의 값을 가지도록 정규화

	// 가우시안 커널을 이미지에 적용할때는 filter2D() 함수를 사용

	////////////////////////////////////////////////////////////



	// Declare variable. (Kernel, Kernel size)
	
	int kernel_size = ceil(2*(4*sigma)+1);
	queue <float> tmp_kernel;
	Mat gau_kernel;



	//내용 구현 : 커널 만들기
	gau_kernel = Mat(kernel_size, kernel_size, -1);
	float tot_gau = 0.0;

	int count = 0; //test
	cout << "OK" << endl;
	cout << "kernel_size:" << kernel_size << endl;
	cout << -int(kernel_size/2) << int(kernel_size/2) << endl;
	for (int row = -int(kernel_size/2); row <= int(kernel_size/2); row++)
		for (int col = -int(kernel_size / 2); col <= int(kernel_size / 2); col++)
		{

			count += 1;
			cout << "(" << row+int(kernel_size / 2) << "," << col+int(kernel_size / 2) << ")" << endl;
			float tmp_pix = 0;
			tmp_pix = (1 / ((2 * CV_PI * pow(sigma, 2))))*exp(-(pow(row, 2) + pow(col, 2)) / (2 * pow(sigma, 2)));
			
			tot_gau += tmp_pix;

			cout << "tmp_pix: " << tmp_pix << " tot_gau: " << tot_gau << endl;
			cout << row + 4 * sigma << col + 4 * sigma << endl;
			tmp_kernel.push(tmp_pix);
			//gau_kernel.at<float>(row + 4 * sigma, col + 4 * sigma) = tmp_pix;

		}
	cout << "test:" << count << endl;

	count = 0;
	for (int i = 0; i < kernel_size; i++)
		for (int j = 0; j < kernel_size; j++)
		{
			count += 1;
			cout << "test:" << count;
			cout << " (" << i << "," << j << ")";
			float now = tmp_kernel.front();
			now = now * (1 / tot_gau);
			cout << " now: " << now << endl;
			gau_kernel.at<float>(i, j) = now;
			tmp_kernel.pop();
		}


	cout << "---------------------Done----------------" << endl;
	filter2D(src, dst, -1, gau_kernel, Point(-1, -1), 0, BORDER_DEFAULT);
	cout << "---------------------Done----------------" << endl;
	// Normalize the kernel

	//내용 구현



	imshow("Window", dst);

	waitKey(0);

	// Apply Gaussian kernel

	//내용 구현

}

//////////////////////////////////////////////





int MatchDescriptor(const Mat &descriptor1, const Mat &descriptor2, vector<int> &machingIdx) {

	///////////////////////////////////////////////////////////////

	// 이미지1의 디스크립터들과 이미지2의 디스크립터들 중 매칭되는 페어의 개수를 계산하는 함수

	// 이미지1의 1개의 디스크립터와 이미지2의 모든 디스크립터 사이의 L2 거리를 계산 

	// 가장 가까운 거리 (d1) 와 두번째로 가까운 거리(d2) 의 비율 (d1/d2) 을 구해 설정된 임계값 (DIST_RATIO_THR) 보다 작다면 매칭으로 판단
	
	// machingIdx 에는 매칭이 된 인덱스를 저장 (machingIdx[idx1] = idx2, idx1은 이미지1의 디스크립터의 인덱스이고, idx2는 매칭된 이미지2의 디스크립터의 인덱스)

	// 함수의 리턴값으로는 매칭된 페어의 개수를 출력

	//////////////////////////////////////////////////////////////


	int numMatches = 0; 
	
	Vector<KeyPoint> kpt1;
	Vector<KeyPoint> kpt2;
	
	machingIdx.resize(descriptor1.rows);

	cout << descriptor1 << endl;


	//내용 구현



	return numMatches;

}