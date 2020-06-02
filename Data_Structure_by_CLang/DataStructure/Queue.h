#pragma once
#include <cstddef>
#include "LinkListStack.h"

typedef struct node2
{
	int data;
	node2* next;
} NODE2;




class Queue
{
public:
	Queue();
	~Queue();

public:
	void Enqueue(int data);
	void Dequeue();
	int Front();
	bool isEmpty();

private:
	NODE2* front;
	NODE2* rear;
	int size;
	
};

