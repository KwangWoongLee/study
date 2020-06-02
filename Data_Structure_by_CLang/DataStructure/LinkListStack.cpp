#include "LinkListStack.h"
#include <iostream>
#include <cstddef>

CLinkListStack::CLinkListStack():
	nTop(NULL)
{
}

CLinkListStack::~CLinkListStack()
{
}

void CLinkListStack::push(DATA data)
{
	NODE* newNode = new NODE;
	newNode->data = data;

	newNode->next = nTop;
	nTop = newNode;
}

DATA CLinkListStack::pop()
{
	NODE* tmpNode;
	DATA returnData;

	if (!isEmpty())
	{
		tmpNode = nTop;
		returnData = nTop->data;
		nTop = nTop->next;

		delete tmpNode;
		return returnData;
	}
	else 
	{
		std::cout << "스택이 비었습니다.";
		return DATA();
	}
	

}

bool CLinkListStack::isEmpty()
{
	if(!nTop)
		return true;

	return false;
}

int CLinkListStack::size()
{
	return 0;
}

DATA CLinkListStack::top()
{
	if (nTop)
		return nTop->data;
}

void CLinkListStack::printStack()
{
	NODE* tmp = nTop;
	
	if (!isEmpty())
	{
		std::cout << tmp->data.x << std::endl;

		while (true)
		{
			if (tmp->next != NULL)
			{
				tmp = tmp->next;
				std::cout << tmp->data.x << std::endl;
			}
			else
				break;
		}

	}
	else
		std::cout << "스택이 비었습니다.";
	
}
