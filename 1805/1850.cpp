#include <iostream>

using namespace std;

long long gcd_sub(long long a, long long b);

long long gcd_recur(long long a, long long b);


int main()
{
	long long a;
	long long b;

	cin >> a >> b;

	long long res = gcd_recur(a, b);

	for (long long i = 0; i < res; ++i)
		cout << "1";



}

long long gcd_sub(long long a, long long b) //시간초과
{
	while (a != 0 and b != 0)
	{
		if (a > b)
		{
			a = a - b;
		}
		else
		{
			b = b - a;
		}
	}

	return a + b;
}

long long gcd_recur(long long a, long long b)
{
	if (a % b == 0)
	{
		return b;
	}
	else
	{
		return gcd_recur(b, a % b);
	}

}