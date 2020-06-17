#include <iostream>

using namespace std;

template <typename T>
void InsertionSort(T arr[], int arrSize)
{
	T tmp;
	int i,j;

	for (i = 1; i < arrSize; ++i)
	{
		tmp = arr[i];

		for (j = i - 1; j >= 0 && arr[j] > tmp; --j)
		{
			arr[j + 1] = arr[j];
		}
		arr[j+1] = tmp;

	}

}

int main() 
{
	int a[] = { 3,6,1,4 };
	InsertionSort<int>(a, sizeof(a) / sizeof(a[0]));

	for (int i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
	{
		cout << a[i];
	}
}