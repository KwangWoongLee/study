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
	/* ��������Ʈ ����
	CStack* stack = new CStack;

	stack->push(1);
	cout << "size :  "  << stack->size() << endl;
	cout << "top : " << stack->top() << endl;
	cout << "pop : " << stack->pop() << endl;
	cout << "size :  " << stack->size() << endl;
	if (!stack->empty())
		cout << "top : " << stack->top() << endl;
	else
		cout << "������ ������ϴ�.";

	*/
	/* ���Ḯ��Ʈ ����
	//���Ḯ��Ʈ������ ��带 ����ϸ�, �Ϲݿ��Ḯ��Ʈ ������ �ݴ��� ������ ���.

	CLinkListStack* stack = new CLinkListStack;
	DATA data;
	data.x = 1;
	stack->push(data);
	data.x = 2;
	stack->push(data);
	stack->pop();
	stack->printStack();
	*/

	/* ���� ť ����.

	Queue* queue = new Queue;

	if (queue->isEmpty())
		std::cout << "ť�� ������ϴ�." << endl;

	queue->Enqueue(1);

	if (queue->isEmpty())
		std::cout << "ť�� ������ϴ�.";
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