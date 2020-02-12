#include "myAlgorithms.h"

int ShakerSort(int *arr, int size)
{
	int l = 0, r = size - 1, k = r;
	while(l != r)
	{
		for (int i = r; i > l; i--)
		{
			if (arr[i] < arr[i-1])
			{
				int temp = arr[i];
				arr[i] = arr[i - 1];
				arr[i - 1] = temp;
				k = i;
			}
		}
		l = k;
		for (int i = l; i < r; i++)
		{
			if (arr[i] > arr[i+1])
			{
				int temp = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = temp;
				k = i;
			}	
		}
		r = k;
	}
}


int main()
{
	srand(time(0));
	int *Arr = new int [10];
	FillRand(Arr, 10, 50);

	cout<<"Array: ";
	PrintArr(Arr, 10);
	ShakerSort(Arr, 10);

	cout << endl << "Sorted array: ";
	PrintArr(Arr, 10);
	return 0;
}