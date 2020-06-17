#include <iostream>

using namespace std;

template <typename T>
void QuickSort(T a[], int arrSize)
{
	int i, j;
	T tmp , pv;

	if (arrSize > 1)
	{
		pv = a[arrSize - 1];
		i = -1;
		j = arrSize - 1; 
		while (true)
		{
			while (a[++i] < pv);
			while (a[--j] > pv);
			if (i >= j) break;
			
			tmp = a[i];
			a[i] = a[j];
			a[j] = tmp;
		}
		tmp = a[i];
		a[i] = a[arrSize - 1];
		a[arrSize -1] = tmp;


		QuickSort(a, i);
		QuickSort(a + i + 1, arrSize - i - 1);
	}


		
}

int main()
{
	int a[] = { 4,9,0,6,7 };
	QuickSort(a, sizeof(a) / sizeof(a[0]));

	for (int i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
	{

		cout << a[i];
	}

}

