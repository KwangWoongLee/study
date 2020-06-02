#pragma once
#include <cstddef>

class CStack
{
public:
	CStack();
	~CStack();

	//스택 기본 함수
	//	추가 및 삭제
	//	push(element) : top에 원소를 추가
	//	pop() : top에 있는 원소를 삭제
	//	조회
	//	top() : top(스택의 처음이 아닌 가장 끝)에 있는 원소를 반환
	//	기타
	//	empty() : 스택이 비어있으면 true 아니면 false를 반환
	//	size() : 스택 사이즈를 반환

	//우선은 스택에 int 타입만을 담을 수 있다고 가정한다.
	//한가지는 일반 배열 , 즉 순차리스트로 구현해본다.
	//순차리스트 배열

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

