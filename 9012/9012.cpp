#include <iostream>
#include <stack>

using namespace std;


int main() 
{

	int n;
	cin >> n;

	

	for (int i = 0; i < n; ++i)
	{
		string s;
		cin >> s;
		stack<char> stack;
		bool emp = true;

		for (int j = 0; j < s.length(); ++j)
		{
			if (s[j] == '(')
				stack.push(s[j]);
			else
			{
				if (!stack.empty())
				{
					stack.pop();
				}
				else
				{
					cout << "NO" << endl;
					emp = false;
					break;
				}
			}
		}

		if (stack.empty() && emp)
		{
			cout << "YES" << endl;
		}
		else if (!stack.empty() && emp)
		{
			cout << "NO" << endl;
		}
	}

}
