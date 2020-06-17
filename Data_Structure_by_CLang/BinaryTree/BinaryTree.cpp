#include "BinaryTree.h"
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

template<typename T>
void BinaryTree<T>::RemoveSubTree(node* pNode)
{
}

template<typename T>
BinaryTree<T>::BinaryTree()
{
	m_pHeadNode = new node;
	m_pTailNode = new node;

	m_pHeadNode->pLeft = m_pTailNode;
	m_pHeadNode->pRight = m_pTailNode;

	m_pTailNode->pLeft = m_pTailNode;
	m_pTailNode->pRight = m_pTailNode;
}

template<typename T>
BinaryTree<T>::~BinaryTree()
{
	RemoveAll();
	if (m_pHeadNode)
	{
		delete m_pHeadNode;
	}

	if (m_pTailNode)
	{
		delete m_pTailNode;
	}
}

template<typename T>
void BinaryTree<T>::RemoveAll()
{
}


template<typename T>
void BinaryTree<T>::Visit(node* pNode)
{
	std::cout << pNode->data;
}

template<typename T>
void BinaryTree<T>::PreorderTraverse_Stack(node* pNode)
{
	stack<node*> stack;
	stack.push(pNode);

	while (!stack.empty())
	{
		pNode = stack.pop();
		if (pNode != m_pTailNode)
		{
			Visit(pNode);
			stack.push(pNode->pLeft);
			stack.push(pNode->pRight);

		}
	}
}

template<typename T>
void BinaryTree<T>::PreorderTraverse_Recursive(node* pNode)
{
	if (pNode != m_pTailNode)
	{
		Visit(pNode);
		PreorderTraverse_Recursive(pNode->pLeft);
		PreorderTraverse_Recursive(pNode->pRight);

	}
}

template<typename T>
void BinaryTree<T>::InorderTraverse_Stack(node* pNode)
{
	//사용 안하는 것을 추천 , 복잡
}

template<typename T>
void BinaryTree<T>::InorderTraverse_Recursive(node* pNode)
{
	if(pNode != m_pTailNode)
	{
		InorderTraverse_Recursive(pNode->pLeft);
		Visit(pNode);
		InorderTraverse_Recursive(pNode->pRight);
	}
}

template<typename T>
void BinaryTree<T>::PostorderTraverse_Stack(node* pNode)
{
	//사용 안하는 것을 추천 , 복잡
}

template<typename T>
void BinaryTree<T>::PostorderTraverse_Recursive(node* pNode)
{

	PostorderTraverse_Recursive(pNode->pLeft);
	PostorderTraverse_Recursive(pNode->pRight);
	Visit(pNode);
}

template<typename T>
void BinaryTree<T>::Levelorder_Traverse(node* pNode)
{
	queue<node*> queue;
	queue.Put(pNode);

	while (!queue.empty())
	{
		pNode = queue.Get();
		if (pNode != m_pTailNode)
		{
			Visit(pNode);
			queue.Put(pNode->pLeft);
			queue.Put(pNode->pRight);
		}
	
	}

}
