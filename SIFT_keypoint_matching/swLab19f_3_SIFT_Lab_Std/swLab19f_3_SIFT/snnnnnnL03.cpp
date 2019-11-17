#include "SIFT.h"
#define DIST_RATIO_THR 0.49
#include <queue>


void customGaussianBlur(const Mat &src, Mat &dst, double sigma) {

	////////////////////////////////////////////////////////////

	// ����þ� Ŀ���� ������ �̹����� �����ϴ� �Լ�

	// Ŀ���� ũ��� 2*(4*sigma)+1 (�Ҽ����� �ø� �Ǵ� �ݿø����� ó���Ѵ�)

	// ����þ� Ŀ���� float���� ���� ����

	// ����þ� Ŀ���� Ŀ�� �� ��� �� ��ü�� �������� ������ 0~1������ ���� �������� ����ȭ

	// ����þ� Ŀ���� �̹����� �����Ҷ��� filter2D() �Լ��� ���

	////////////////////////////////////////////////////////////



	// Declare variable. (Kernel, Kernel size)
	
	int kernel_size = ceil(2*(4*sigma)+1);
	queue <float> tmp_kernel;
	Mat gau_kernel;



	//���� ���� : Ŀ�� �����
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

	//���� ����



	imshow("Window", dst);

	waitKey(0);

	// Apply Gaussian kernel

	//���� ����

}

//////////////////////////////////////////////





int MatchDescriptor(const Mat &descriptor1, const Mat &descriptor2, vector<int> &machingIdx) {

	///////////////////////////////////////////////////////////////

	// �̹���1�� ��ũ���͵�� �̹���2�� ��ũ���͵� �� ��Ī�Ǵ� ����� ������ ����ϴ� �Լ�

	// �̹���1�� 1���� ��ũ���Ϳ� �̹���2�� ��� ��ũ���� ������ L2 �Ÿ��� ��� 

	// ���� ����� �Ÿ� (d1) �� �ι�°�� ����� �Ÿ�(d2) �� ���� (d1/d2) �� ���� ������ �Ӱ谪 (DIST_RATIO_THR) ���� �۴ٸ� ��Ī���� �Ǵ�
	
	// machingIdx ���� ��Ī�� �� �ε����� ���� (machingIdx[idx1] = idx2, idx1�� �̹���1�� ��ũ������ �ε����̰�, idx2�� ��Ī�� �̹���2�� ��ũ������ �ε���)

	// �Լ��� ���ϰ����δ� ��Ī�� ����� ������ ���

	//////////////////////////////////////////////////////////////


	int numMatches = 0; 
	
	Vector<KeyPoint> kpt1;
	Vector<KeyPoint> kpt2;
	
	machingIdx.resize(descriptor1.rows);

	cout << descriptor1 << endl;


	//���� ����



	return numMatches;

}