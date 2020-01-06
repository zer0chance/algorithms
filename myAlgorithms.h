#include <iostream>
#include <ctime>
#include <cstdlib>

#define FillRand(A, size, rand_range) for (int i = 0; i < size, i++) A[i] = rand() % rand_range;
#define PtintArr(A, size) for (int i = 0; i < size; i++) cout << A[i] << " ";

int CheckSum (int *arr, int size)
{
    int sum;
    for (int i = 0, sum = 0; i < size; i++) sum += arr[i];
    return sum;
}

int RunNumber (int *arr, int size)
{
	int srs = 1;
	for (int i = 1; i < N; i++) if (arr[i] < arr[i-1]) srs++;  
	return srs;
}
