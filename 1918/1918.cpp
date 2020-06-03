#include <iostream>
#include <stack>
#include <string>

using namespace std;

void insertOp(char c,stack<char>* op, stack<char>* sp);

int main()
{
	string s;
	cin >> s;
	
	stack<char>* opStack = new stack<char>;
	stack<char>* outStack = new stack<char>;

	for (int i = 0; i < s.length(); ++i)
	{
		char op = NULL;

		if (s[i] == '(')
			opStack->push(s[i]);

		else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/')
		{
			insertOp(s[i],opStack,outStack);
		}

		else if (s[i] == ')')
		{
			while (op != '(')
			{
				op = opStack->top();
				opStack->pop();
				if (op != '(')
					outStack->push(op);
			}
		}

		else
		{
			outStack->push(s[i]);
		}
	}

	while (!opStack->empty())
	{
		outStack->push(opStack->top());
		opStack->pop();
	}

	while (!outStack->empty())
	{
		cout <<outStack->top();
		outStack->pop();
	}
	
}

void insertOp(char s, stack<char>* pOp,stack<char>* pOs)
{
	if (s == '+' || s == '-')
	{
		while (pOp->top()=='*' || pOp->top()=='/')
		{
			pOs->push(pOp->top());
			pOp->pop();
		}
		pOp->push(s);
	}
	else
	{
		pOp->push(s);
	}
}