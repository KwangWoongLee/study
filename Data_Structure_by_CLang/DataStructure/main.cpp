#include "SimpleLinkList.h"
#include "Stack.h"
#include "LinkListStack.h"
#include "Queue.h"

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
	/* 순차리스트 스택
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
	/* 연결리스트 스택
	//연결리스트스택은 노드를 사용하며, 일반연결리스트 구현의 반대적 느낌이 든다.

	CLinkListStack* stack = new CLinkListStack;
	DATA data;
	data.x = 1;
	stack->push(data);
	data.x = 2;
	stack->push(data);
	stack->pop();
	stack->printStack();
	*/

	/* 선형 큐 구현.

	Queue* queue = new Queue;

	if (queue->isEmpty())
		std::cout << "큐가 비었습니다." << endl;

	queue->Enqueue(1);

	if (queue->isEmpty())
		std::cout << "큐가 비었습니다.";
	else
	{
		std::cout << queue->Front() << endl;
		;
	}

	queue->Enqueue(2);
	queue->Enqueue(3);
	queue->Enqueue(4);
	queue->Enqueue(5);

	queue->Dequeue();
	queue->Dequeue();
	*/



}
