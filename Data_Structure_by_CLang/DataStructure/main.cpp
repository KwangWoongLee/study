#include "SimpleLinkList.h"
#include "Stack.h"
#include "LinkListStack.h"
#include <iostream>

using namespace std;

int main()
{

	/*	SimpleLinkList
	CSimpleLinkList* list = new CSimpleLinkList;

	list->PushFront(1);
	list->PushFront(2);
	list->PushBack(3);
	CSimpleLinkList::Iterator keyIter = list->FindKey(1);
	list->InsertNext(keyIter,4);

	list->ViewAll();
	*/	
	/*
	CStack* stack = new CStack;

	stack->push(1);
	cout << "size :  "  << stack->size() << endl;
	cout << "top : " << stack->top() << endl;
	cout << "pop : " << stack->pop() << endl;
	cout << "size :  " << stack->size() << endl;
	if (!stack->empty())
		cout << "top : " << stack->top() << endl;
	else
		cout << "스택이 비었습니다.";

	*/

	CLinkListStack* stack = new CLinkListStack;
	DATA data;
	data.x = 1;
	stack->push(data);
	data.x = 2;
	stack->push(data);
	stack->pop();
	stack->printStack();
	

}
