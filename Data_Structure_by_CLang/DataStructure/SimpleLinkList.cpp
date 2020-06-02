#include <iostream>
#include "SimpleLinkList.h"

using namespace std;

CSimpleLinkList::CSimpleLinkList()	:
	m_prev(NULL),
	m_head(NULL),
	m_tail(NULL)
{
}

CSimpleLinkList::~CSimpleLinkList()
{
	while (m_head)
	{
		m_prev = m_head;
		m_head = m_head->next;
		
		delete m_prev;
	}
}

Node* CSimpleLinkList::end()
{	

	return NULL;
}

Node* CSimpleLinkList::begin()
{
	return m_head;
}

void CSimpleLinkList::PushFront(int data)
{
	Node* node = new Node(data);

	if (!m_head)
	{
		m_head = node;
		m_tail = node;
	}

	else
	{
		node->next = m_head;
		m_head = node;
	}

}

void CSimpleLinkList::PushBack(int data)
{
	Node* node = new Node(data);

	if (!m_head)
	{
		m_head = node;
		m_tail = node;
	}
	else
	{
		m_tail->next = node;
		m_tail = node;
	}
}

CSimpleLinkList::Iterator CSimpleLinkList::FindKey(int key)
{
	CSimpleLinkList::Iterator iter = this->begin();
	CSimpleLinkList::Iterator iterEnd = this->end();

	for (; iter != iterEnd; iter.next())
	{
		if (iter.node->data == key)
		{
			return iter;
		}
	}

	return NULL;
}

void CSimpleLinkList::InsertNext(Iterator pIter, int data)
{
	Node* node = new Node(data);

	node->next = pIter.node->next;
	pIter.node->next = node;

}

void CSimpleLinkList::ViewAll()
{
	CSimpleLinkList::Iterator iter = this->begin();
	CSimpleLinkList::Iterator iterEnd = this->end();

	for (; iter != iterEnd; iter.next())
	{
		cout << iter.node->data;
	}
}
