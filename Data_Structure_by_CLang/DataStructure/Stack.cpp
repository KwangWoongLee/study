#include "Stack.h"
using namespace std;


CStack::CStack()	:
	iTop(-1)
{
}

CStack::~CStack()
{
}

int CStack::size()
{
	return iTop+1;
}

bool CStack::empty()
{
	if (iTop == -1)
		return true;
	return false;
}

int CStack::top()
{
	if(iTop>-1)
		return iStack[iTop];

	return NULL;
}

int CStack::pop()
{
	if(iTop>-1)
		return iStack[iTop--];

	return NULL;
}

void CStack::push(int data)
{
	++iTop;
	iStack[iTop] = data;
}
