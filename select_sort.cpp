#include "myAlgorithms.h"

void SelectSort (int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
		int k = i, j;
        for (j = i + 1; j < size; j++)
      	{
      		if (arr[j] < arr[k]) k = j;
		}

		if (arr[i] != arr[j])
		{
			int temp = arr[i];
			arr[i] = arr[k];
			arr[k] = temp;
		}
	}
}


int main()
{
	srand(time(0));
	int *Arr = new int [10];
	FillRand(Arr, 10, 50);

	cout<<"Array: ";
	PrintArr(Arr, 10);
	SelectSort(Arr, 10);

	cout << endl << "Sorted array: ";
	PrintArr(Arr, 10);
	return 0;
}