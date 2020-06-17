#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main()
{
	int n;
	cin >> n;
	stack<int> stack;
	string str;

	for (int i = 0; i < n; ++i)
	{
		cin >> str;
		
		if (str == "push")
		{
			cin >> str;
			stack.push(stoi(str));
		}
		else if (str == "pop")
		{
			if (stack.size() == 0)
				cout << -1 << endl;
			else
			{
				cout << stack.top() << endl;
				stack.pop();
			}
		}
		else if (str == "top")
		{
			if (stack.size() == 0)
				cout << -1 << endl;
			else
			{
				cout << stack.top() << endl;
			}
		}
		else if (str == "size")
		{
			cout << stack.size() << endl;
		}
		else if (str == "empty")
		{
			if (stack.empty())
				cout << 1 << endl;
			else
				cout << 0 << endl;
		}
	}
}
