#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <omp.h>
#include <locale.h>
#include <iostream>
#include <windows.h>


using std::cout;

int main()
{
	int n, N, rank, k, i; // num of threads, Array size, rank
	float Sum = 0;
	scanf("%d", &n);
	scanf("%d", &N);
	omp_set_num_threads(n);
#pragma omp parallel shared(rank)
	{
		rank = omp_get_thread_num();
		Sleep(100);
		printf("I am %d thread\n", rank);
	}
	cout << "*******************\n";
#pragma omp parallel private(rank)
	{
		rank = omp_get_thread_num();
		printf("I am %d thread\n", rank);
	}

	float* Array = new float[N];
	srand(time(NULL));
	for (int i = 0; i < N; i++) {
		Array[i] = (float)rand() / RAND_MAX * (23.0 * 3.0 - 23.0 - 3.0) + (23.0 - 3.0);
	}

#pragma omp parallel num_threads(2) reduction(+:Sum)
	{
		if (omp_get_thread_num() != 1){
			for (int i = 0; i < N / 2; i++)
			{
				Sum += Array[i];
			}
		}
		else{
			for (int i = N/2; i < N; i++){
				Sum += Array[i];
			}
		}
		printf("[%d]: Sum = %f\n", omp_get_thread_num(), Sum);
	}
	printf("Sum = %f\n", Sum);
	cout << "*************************\n";
	scanf("%d", &k);
	
	omp_set_num_threads(k);
	Sum = 0;
#pragma omp parallel num_threads(k) reduction(+:Sum)
	{
		int lowerBound = omp_get_thread_num() * N / k;
		int upperBound = (omp_get_thread_num() + 1) * N / k;

		for (int i = lowerBound; i < upperBound; i++) {
			Sum += Array[i];
		}
		printf("[%d]: Sum = %f\n", omp_get_thread_num(), Sum);
	}
	printf("Sum = %f\n", Sum);

	return 0;
}