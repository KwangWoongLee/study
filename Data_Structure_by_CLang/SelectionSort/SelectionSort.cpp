#include <iostream>

using namespace std;

template <typename T>
void SelectionSort(T arr[], int arrSize)
{
	int minIdx; 
	int min;
	for (int i = 0; i < arrSize; ++i)
	{
		minIdx = i;
		min = arr[i];
		for (int j = i + 1; j < arrSize; ++j)
		{
			if (arr[j] < min)
				minIdx = j;
		}

		min = arr[minIdx];
		arr[minIdx] = arr[i];
		arr[i] = min;
	}
}



int main() {
	int a[] = { 3,2,4 };
	SelectionSort<int>(a, sizeof(a)/sizeof(a[0]));

	for (int i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
		cout << a[i];

}

