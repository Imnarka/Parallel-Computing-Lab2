#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <omp.h>
#include <locale.h>
#include <iostream>
#include <windows.h>


using std::cout;

void problem1(int rank) {
#pragma omp parallel shared(rank)
	{
		rank = omp_get_thread_num();
		Sleep(100);
		printf("I am %d thread\n", rank);
	}
}

void problem2(int rank) {
#pragma omp parallel private(rank)
	{
		rank = omp_get_thread_num();
		printf("I am %d thread\n", rank);
	}
}

void problem3(int N, float* Array, float Sum) {
#pragma omp parallel num_threads(2) reduction(+:Sum)
	{
		if (omp_get_thread_num() != 1) {
			for (int i = 0; i < N / 2; i++) {
				Sum += Array[i];
			}
		}
		else {
			for (int i = N / 2; i < N; i++) {
				Sum += Array[i];
			}
		}
		printf("[%d]: Sum = %f\n", omp_get_thread_num(), Sum);
	}
	printf("Sum = %f\n", Sum);
}

void problem4(int N, float* Array, float Sum, int k) {
	
	scanf("%d", &k);
	omp_set_num_threads(k);

#pragma omp parallel num_threads(k) reduction(+:Sum)
	{
		int lowerBound = (N / k) * omp_get_thread_num();
		int upperBound = (N / k) * (omp_get_thread_num() + 1);

		for (int i = lowerBound; i < upperBound; i++) {
			Sum += Array[i];
		}
		printf("[%d]: Sum = %f\n", omp_get_thread_num(), Sum);
	}
	printf("Sum = %f\n", Sum);
}

int main()
{
	int N, rank, k, i; // num of threads, Array size, rank
	float Sum = 0;
	scanf("%d", &k);
	scanf("%d", &N);
	omp_set_num_threads(k);
	problem1(rank);
	cout << "*******************\n";
	problem2(rank);

	float* Array = new float[N];
	srand(time(NULL));
	for (int i = 0; i < N; i++) {
		
		Array[i] = (double)rand() / RAND_MAX * (23*3 - (23-3)) + (23-3);
	}
	problem3(N, Array, Sum);
	cout << "*******************\n";
	Sum = 0;
	k = 0;
	problem4(N, Array, Sum,k);
	return 0;
}