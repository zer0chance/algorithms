#include "myAlgorithms.h"

void BubbleSort (int *arr, int size)
{
	for (int i = 0; i < size-1; i++)
        for (int j = size; j > 0; j--)
        { 
            if(arr[j] < arr[j - 1])
            {
                int temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp; 	
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
	BubbleSort(Arr, 10);

	cout << endl << "Sorted array: ";
	PrintArr(Arr, 10);
	return 0;
}