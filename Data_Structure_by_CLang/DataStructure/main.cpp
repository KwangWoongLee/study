#include "SimpleLinkList.h"

int main()
{
	CSimpleLinkList* list = new CSimpleLinkList;

	list->PushFront(1);
	list->PushFront(2);
	list->PushBack(3);
	CSimpleLinkList::Iterator keyIter = list->FindKey(1);
	list->InsertNext(keyIter,4);

	list->ViewAll();
}