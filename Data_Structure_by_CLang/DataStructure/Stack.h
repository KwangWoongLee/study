#pragma once
#include <cstddef>

class CStack
{
public:
	CStack();
	~CStack();

	//���� �⺻ �Լ�
	//	�߰� �� ����
	//	push(element) : top�� ���Ҹ� �߰�
	//	pop() : top�� �ִ� ���Ҹ� ����
	//	��ȸ
	//	top() : top(������ ó���� �ƴ� ���� ��)�� �ִ� ���Ҹ� ��ȯ
	//	��Ÿ
	//	empty() : ������ ��������� true �ƴϸ� false�� ��ȯ
	//	size() : ���� ����� ��ȯ

	//�켱�� ���ÿ� int Ÿ�Ը��� ���� �� �ִٰ� �����Ѵ�.
	//�Ѱ����� �Ϲ� �迭 , �� ��������Ʈ�� �����غ���.
	//��������Ʈ �迭

private:
	int		iTop;
	int		iStack[100] = {0,};

public:
	int size();
	bool empty();
	int top();
	int pop();
	void push(int data);

};
