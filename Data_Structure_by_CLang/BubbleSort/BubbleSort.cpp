#include <iostream>

using namespace std;

template <typename T>
void BubbleSort(T a[], int arrSize)
{
	T tmp;
	for (int i = 0; i < arrSize -1 ; ++i)
	{
		for (int j = 1; j < arrSize - i; ++j)
		{
			if (a[j - 1] > a[j])
			{
				tmp = a[j - 1];
				a[j - 1] = a[j];
				a[j] = tmp;
			}
		}
	}
};

int main()
{
	int arr[] = { 4,5,3,1,0,-1,9 };
	int arrSize = sizeof(arr) / sizeof(arr[0]);

	BubbleSort(arr, arrSize);

	for (int i = 0; i < arrSize; ++i)
	{
		cout << arr[i];
	}
}