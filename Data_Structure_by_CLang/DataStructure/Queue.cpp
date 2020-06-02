#include "Queue.h"
#include <iostream>
#include <cstddef>

Queue::Queue()	:
	front(NULL),
	rear(NULL),
	size(0)
{
}

Queue::~Queue()
{
}

void Queue::Enqueue(int data)
{
	NODE2* newNode = new NODE2;
	newNode->data = data;

	if (isEmpty())
	{
		front = newNode;
		rear = newNode;
		size = 1;
	}

	else
	{
		rear->next = newNode;
		rear = newNode;
		++size;
	}

}

void Queue::Dequeue()
{

	if (isEmpty())
		std::cout << "큐가 비었습니다" << std::endl;
	else
	{
		NODE2* tmp = front;
		front = front->next;
		--size;

		delete tmp;
	}
}

int Queue::Front()
{
	return front->data;
}

bool Queue::isEmpty()
{
	if (!size)
		return true;
	return false;
}
