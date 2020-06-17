#pragma once

template <typename T> 
class BinaryTree
{

protected:
	struct node
	{
		node* pLeft;
		node* pRight;
		T	  data;

	};

	node*	m_pHeadNode;
	node*	m_pTailNode;
	void RemoveSubTree(node* pNode);

public:
	BinaryTree();
	~BinaryTree();
	void RemoveAll();
	
	void Visit(node* pNode);
	
	void PreorderTraverse_Stack(node* pNode);
	void PreorderTraverse_Recursive(node* pNode);
	
	void InorderTraverse_Stack(node* pNode);
	void InorderTraverse_Recursive(node* pNode);
	
	void PostorderTraverse_Stack(node* pNode);
	void PostorderTraverse_Recursive(node* pNode);
	
	void Levelorder_Traverse(node* pNode);
};

