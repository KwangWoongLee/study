#pragma once

typedef struct data
{
	int x;
} DATA;

typedef struct node
{
	DATA data;
	node* next;

} NODE, *PNODE;


class CLinkListStack
{
public:
	CLinkListStack();
	~CLinkListStack();

private:
	NODE*	nTop;

public:
	void push(DATA data);
	DATA pop();
	bool isEmpty();
	int size();
	DATA top();
	void printStack();

};

