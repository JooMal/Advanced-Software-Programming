#include "header.h"

// 다항 함수 방정식 f(x)=0의 근을 구하는 함수
void problem1() {
	int degree = n - 1;
	double *zeror, *zeroi; // 근의 실수와 허수 part
	long int fail;

	zeror = (double *)malloc(sizeof(double)*degree);
	zeroi = (double *)malloc(sizeof(double)*degree);

	printf("*** Roots finding for an n-th degree polynomial using RPOLY\n");
	for (int i = 0; i < degree; i++) {
		printf("%.4lfx^%d + ", x[i], degree - i);
	}
	printf("%.4lf = 0\n", x[degree]);

	// Fortran 함수 호출
	rpoly_(x, &degree, zeror, zeroi, &fail);

	printf("\nfail = %d\n", fail);
	// 구한 모든 근(실근, 허근)을 출력
	for (int i = 0; i < degree; i++)
		printf("r(%2d) = (%.10lf) + (%.10lf) i\n", i + 1, zeror[i], zeroi[i]);
	printf("\n");

	double fx = -1.0;
	for (int i = 0; i < degree; i++) {
		if (zeroi[i] != 0.0)
			continue;
		// ***TO_DO*** (실습 전 준비 및 연습, 실습 1)
				// 실근에 한하여 f(zeror[i])의 값 fx를 구하는 코드를 작성한다 ***
				// Honer's rule을 사용한다(인터넷을 검색해 알아보자)
		else
		{
			fx = x[0];
			for (int k = 1; k < degree + 1; k++)
			{
				fx = (fx*zeror[i]) + x[k];
			}
		}


		// ***END OF TO_DO***
		printf("f(%.15lf) = %.15lf\n", zeror[i], fx);
	}
	free(zeror);
	free(zeroi);
	return;
}

// HYBRJ1
// f1 = 3 * x_1 - cos(x_2* x_3) - 0.5;
// f2 = x_1 * x_1 - 81.0*(x_2 + 0.1)^2 + sin(x_3) + 1.06;
// f2 = exp(-x_1 * x_2) + 20.0*x_3 + (10.0*M_PI - 3.0) / 3.0;
void problem2_(int *n, double *x, double *fvec, double *fjac, int *ldfjac, int *iflag)
{
	//printf("!!!!\n");
// ***TO_DO*** (실습 2)
	// *iflag=1이면 f(x)를 계산하여 fvec에 저장한다.
	// *iflag=2이면 Jacobian F(x)를 계산하여 fjac에 column major order로 저장한다.
	// origin function f(x)

	//printf("n : %d\nx : %d\n", *n, *x);

	if (*iflag == 1)
	{
		fvec[0] = 3 * x[0] - cos(x[1] * x[2]) - 0.5;
		fvec[1] = x[0] * x[0] - 81.0*(x[1] + 0.1)*(x[1] + 0.1) + sin(x[2]) + 1.06;
		fvec[2] = exp(-x[0] * x[1]) + 20.0*x[2] + (10.0*M_PI - 3.0) / 3.0;
	}
	else if (*iflag == 2)
	{
		// 편미분한 자코비안 행렬을 적어주면 된다
		fjac[0] = 3.0;	fjac[3] = x[2] * sin(x[1] * x[2]);	fjac[6] = x[1] * sin(x[1] * x[2]);
		fjac[1] = 2.0*x[0];		fjac[4] = -162.0*(x[1] + 0.1);	fjac[7] = cos(x[2]);
		fjac[2] = -x[1] * exp(x[0] * x[1]); fjac[5] = -x[0] * exp(-x[0] * x[1]); fjac[8] = 20.0;

	}



	// ***END OF TO_DO***
	return;
}

// HYBRD1
// f1 = 3 * x_1 - cos(x_2* x_3) - 0.5;
// f2 = x_1 * x_1 - 81.0*(x_2 + 0.1)^2 + sin(x_3) + 1.06;
// f2 = exp(-x_1 * x_2) + 20.0*x_3 + (10.0*M_PI - 3.0) / 3.0;
void problem3_(int *n, double *x, double *fvec, int *iflag)
{
	// ***TO_DO*** (실습 3)
		// f(x)를 계산하여 fvec에 저장한다.

	fvec[0] = 3 * x[0] - cos(x[1] * x[2]) - 0.5;
	fvec[1] = x[0] * x[0] - 81.0*(x[1] + 0.1)*(x[1] + 0.1) + sin(x[2]) + 1.06;
	fvec[2] = exp(-x[0] * x[1]) + 20.0*x[2] + (10.0*M_PI - 3.0) / 3.0;

	return;
	// ***END OF TO_DO***
}

// HYBRJ1
// f1 = exp(2*x_1) - x_2 + 4 = 0
// f2 = x_2 - x_3 - 1 = 0
// f3 = x_3 - sin(x_1) = 0
void problem4_(int *n, double *x, double *fvec, double *fjac, int *ldfjac, int *iflag)
{
	// ***TO_DO*** (실습 4)
		// 작성 방법은 실습 2와 동일하다
	if (*iflag == 1)
	{
		fvec[0] = exp(2 * x[0]) - x[1] + 4;
		fvec[1] = x[1] - x[2] - 1;
		fvec[2] = x[2] - sin(x[0]);
	}
	else if (*iflag == 2)
	{
		fjac[0] = 2 * exp(2 * x[0]); fjac[3] = -1; fjac[6] = 0;
		fjac[1] = 0; fjac[4] = 1; fjac[7] = -1;
		fjac[2] = -cos(x[0]); fjac[5] = 0; fjac[8] = 1;
	}


	// ***END OF TO_DO***
}

// HYBRD1
// f1 = exp(2*x_1) - x_2 + 4 = 0
// f2 = x_2 - x_3 - 1 = 0
// f3 = x_3 - sin(x_1) = 0
void problem5_(int *n, double *x, double *fvec, int *iflag)
{
	// ***TO_DO*** (실습 5)
			// 작성 방법은 실습 3과 동일하다

	fvec[0] = exp(2 * x[0]) - x[1] + 4;
	fvec[1] = x[1] - x[2] - 1;
	fvec[2] = x[2] - sin(x[0]);

	// ***END OF TO_DO***
	return;
}

// HYBRJ1
// f1 = x_1 + 10 * x_2 + 9;
// f2 = sqrt(5.0) * (x_3 - x_4) - 2 * sqrt(5.0);
// f3 = (x_2 - 2 * x_3)^2 - 9;
// f4 = sqrt(10.0)*(x_1 - x_4, 2)^2 - 2 * sqrt(10.0);
void homework1_j(int *n, double *x, double *fvec, double *fjac, int *ldfjac, int *iflag) {
	// ***TO_DO*** (숙제 1)
	if (*iflag == 1)
	{
		fvec[0] = x[0]+10*x[1]+9;
		fvec[1] = sqrt(5.0)*(x[2]-x[3])-2*sqrt(5.0);
		fvec[2] = (x[1]-2*x[2])*(x[1]-2*x[2])-9;
		fvec[3] = sqrt(10.0)*(x[0] - x[3])*(x[0] - x[3]) - 2 * sqrt(10.0);

	}
	else if (*iflag == 2)
	{
		fjac[0] = 2 * exp(2 * x[0]); fjac[3] = -1; fjac[6] = 0;
		fjac[1] = 0; fjac[4] = 1; fjac[7] = -1;
		fjac[2] = -cos(x[0]); fjac[5] = 0; fjac[8] = 1;

		fjac[0] = 1; fjac[4] = 10; fjac[8] = 0; fjac[12] = 0;
		fjac[1] = 0; fjac[5] = 0; fjac[9] = sqrt(5.0)*x[2]; fjac[13] = -sqrt(5.0)*x[3];
		fjac[2] = 0; fjac[6] = 2 * x[1] - 4 * x[2]; fjac[10] = -4 * x[1] + 8 * x[2]; fjac[14] = 0;
		fjac[3] = sqrt(10.0)*(2 * x[0] - 2 * x[3]); fjac[7] = 0; fjac[11] = 0; fjac[15] = sqrt(10.0)*(-2 * x[0] + 2 * x[3]);
	}

	// ***END OF TO_DO***
	return;
}

// HYBRD1
// f1 = x_1 + 10 * x_2 + 9;
// f2 = sqrt(5.0) * (x_3 - x_4) - 2 * sqrt(5.0);
// f3 = (x_2 - 2 * x_3)^2 - 9;
// f4 = sqrt(10.0)*(x_1 - x_4, 2)^2 - 2 * sqrt(10.0);
void homework2_d(int *n, double *x, double *fvec, int *iflag)
{
	// ***TO_DO*** (숙제 2)

	fvec[0] = x[0] + 10 * x[1] + 9;
	fvec[1] = sqrt(5.0)*(x[2] - x[3]) - 2 * sqrt(5.0);
	fvec[2] = (x[1] - 2 * x[2])*(x[1] - 2 * x[2]) - 9;
	fvec[3] = sqrt(10.0)*(x[0] - x[3])*(x[0] - x[3]) - 2 * sqrt(10.0);

	// ***END OF TO_DO***
	return;
}

int main() {

	int test_case;
	int problem;

	scanf("%d", &test_case);

	for (int i = 0; i < test_case; i++) {
		printf("Test %d\n", i);
		scanf("%d", &problem);

		scanf("%d", &n);
		if (problem == p1)
			n++;
		x = (double*)malloc(sizeof(double)*(n));
		for (int i = 0; i < n; i++)
			scanf("%lf", &x[i]);

		switch (problem) {
		case p1:
			problem1();
			break;
		case p2:
			fcn_j = problem2_;
			solve_hybrj1();
			break;
		case p3:
			fcn_d = problem3_;
			solve_hybrd1();
			break;
		case p4:
			fcn_j = problem4_;
			solve_hybrj1();
			break;
		case p5:
			fcn_d = problem5_;
			solve_hybrd1();
			break;
		case h1:
			fcn_j = homework1_j;	// problem 6
			solve_hybrj1();
			break;
		case h2:
			fcn_d = homework2_d;	// problem 7
			solve_hybrd1();
			break;
		}
		free(x);	// free allocated memory for x
		if (i != test_case - 1)
			printf("\n");
	}
	return 0;
}

void solve_hybrj1() {
	printf("*** Roots finding for nonlinear equations using HYBRJ1\n");
	printf("  Initial values of X\n");
	for (int i = 0; i < n; i++)	// read initial values of x[]
		printf("    x_%d = %lf\n", i + 1, x[i]);

	// ***TO_DO*** (실습 2)
		// 1. header.h에서 선언한 n, x, fvec, info를 제외한 
		//    hybrj1_()에 필요한 parameter 변수 선언
		// 2. 배열의 경우 필요한 만큼 dynamic allocation
		// 3. hybrj1_()의 parameter 변수들의 초기 값 설정
		// 4. hybrj1_() 호출
		// 5. x의 초기 값, info flag 값, 구한 근의 근사 값 x[] 및 이들 각각의
		//    f(x) 값 출력 (실습 자료의 출력 format 참조)
		// 6. 이 함수에서 allocation한 메모리 deallocation


		// 1. header.h에서 선언한 n, x, fvec, info를 제외한 
		//    hybrj1_()에 필요한 parameter 변수 선언
	double *fjac;
	int ldfjac;
	int iflag;
	double tol;
	double *wa;
	int lwa;

	// 2. 배열의 경우 필요한 만큼 dynamic allocation
	fvec = (double*)malloc(sizeof(double)*(n));
	fjac = (double*)malloc(sizeof(double)*(n*n));
	lwa = 3 * n * (n + 13) / 2;
	wa = (double*)malloc(sizeof(double)*(lwa));

	// 3. hybrj1_()의 parameter 변수들의 초기 값 설정
	ldfjac = n;
	tol = TOLERANCE;

	// 4. hybrj1_() 호출
	hybrj1_(fcn_j, &n, x, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);

	// 5. x의 초기 값, info flag 값, 구한 근의 근사 값 x[] 및 이들 각각의
	//    f(x) 값 출력 (실습 자료의 출력 format 참조)
	printf("\ninfo = %d\n", info);

	printf("root=\t%.8lf", x[0]);
	for (int i = 1; i < n; i++)
	{
		printf("\t%.8lf", x[i]);
	}
	printf("\nf(x)=\t%.8lf", fvec[0]);
	for (int i = 1; i < n; i++)
	{
		printf("\t%.8lf", fvec[i]);
	}


	// 6. 이 함수에서 allocation한 메모리 deallocation
	free(fvec);
	free(fjac);
	free(wa);

	// ***END OF TO_DO***
	return;
}

void solve_hybrd1() {
	printf("*** Roots finding for nonlinear equations using HYBRD1\n");
	printf("  Initial values of X\n");
	for (int i = 0; i < n; i++)
		printf("    x_%d = %lf\n", i + 1, x[i]);
	// ***TO_DO*** (실습 3)
		// 1. header.h에서 선언한 n, x, fvec, info를 제외한 
		//    hybrd1_()에 필요한 parameter 변수 선언
		// 2. 배열의 경우 필요한 만큼 dynamic allocation
		// 3. hybrd1_()의 parameter 변수들의 초기 값 설정
		// 4. hybrd1_() 호출
		// 5. x의 초기 값, info flag 값, 구한 근의 근사 값 x[] 및 이들 각각의
		//    f(x) 값 출력 (실습 자료의 출력 format 참조)
		// 6. 이 함수에서 allocation한 메모리 deallocation


	int ldfjac;
	int iflag;
	double tol;
	double *wa;
	int lwa = 3 * n * (n + 13) / 2;

	fvec = (double*)malloc(sizeof(double)*(n));
	wa = (double*)malloc(sizeof(double)*(lwa));


	ldfjac = 0;
	tol = TOLERANCE;

	hybrd1_(*fcn_d, &n, x, fvec, &tol, &info, wa, &lwa);

	printf("\ninfo = %d\n", info);

	printf("root=\t%.8lf", x[0]);
	for (int i = 1; i < n; i++)
	{
		printf("\t%.8lf", x[i]);
	}
	printf("\nf(x)=\t%.8lf", fvec[0]);
	for (int i = 1; i < n; i++)
	{
		printf("\t%.8lf", fvec[i]);
	}

	free(fvec);
	free(wa);
	// ***END OF TO_DO***
	return;
}