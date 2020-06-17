#include <iostream>

using namespace std;

template <typename T>
int BinarySearch(T key, T a[], int arrSize)
{
	int l = 0;
	int r = arrSize - 1;
	int mid; 

	while (r >= l)
	{
		mid = (r + l) / 2;
		if (a[mid] == key)	return mid; 
		if (a[mid] > key)
			r = mid - 1;
		else
			l = mid + 1;
	}
	// 찾지 못한 경우 
	
	return NULL;
};

int main() 
{
	char a[] = { 'A', 'B', 'C', 'D' };

	int keyIdx = BinarySearch('A', a, 4);

	cout << keyIdx;

}

