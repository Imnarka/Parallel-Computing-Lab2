#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <omp.h>
#include <locale.h>
#include <iostream>
#include <windows.h>


using std::cout;

int main()
{
	int n; // num of threads
	scanf("%d", &n);

	omp_set_num_threads(n);
	
#pragma omp parallel
	{
		srand(int(time(NULL)) * omp_get_thread_num());
		int rank = omp_get_thread_num(); //shared variable
		//Sleep(100);
		printf("I am %d thread\n", rank); // print shared variable (zero)
	}

	return 0;
}