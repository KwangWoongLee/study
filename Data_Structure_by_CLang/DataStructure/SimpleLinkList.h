#pragma once
#include <cstddef>

struct Node
{
	int data;
	Node* next;
	
	Node(int data = 0) 
	{
		this->data = data;
		next = NULL;
	}

};

class CSimpleLinkList
{
	Node* m_head;
	Node* m_tail;
	Node* m_prev;

public:
	CSimpleLinkList();
	~CSimpleLinkList();

public:
	class Iterator 
	{
		Node* node;

	public:
		friend class CSimpleLinkList;

		Iterator(Node* node = NULL)
		{
			this->node = node; 
		};
		
		bool operator==(const Iterator& iter)
		{
			if(iter.node == node)
				return true;
			return false;
		}

		bool operator!=(const Iterator& iter)
		{
			if (iter.node != node)
				return true;
			return false;
		}

		void next()
		{
			node = (node)->next;
		}

	};

	Node* end();
	Node* begin();
	void PushFront(int data);
	void PushBack(int data);
	Iterator FindKey(int key);
	void InsertNext(Iterator iter,int data);
	void ViewAll();


};

