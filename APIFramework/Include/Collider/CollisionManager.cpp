#include "CollisionManager.h"
#include "../Object/Obj.h"
#include "Collider.h"

DEFINITION_SINGLE(CCollisionManager);

CCollisionManager::CCollisionManager()
{

}

CCollisionManager::~CCollisionManager()
{ 

}

bool CCollisionManager::Init()
{
	return true;
}

void CCollisionManager::AddObject(CObj* pObj)
{
	if (pObj->CheckCollider())
	{
		m_CollisionList.push_back(pObj); 
	}
}

void CCollisionManager::Collision(float fDeltaTime)
{
	if (m_CollisionList.size() < 2)
	{
		m_CollisionList.clear();
		return;
	}
	
	//������Ʈ�� �浹ó���� �Ѵ�.
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_CollisionList.end();
	--iterEnd;

	for (iter = m_CollisionList.begin(); iter != iterEnd; ++iter)
	{
		list<CObj*>::iterator iter1 = iter;
		++iter1;
		list<CObj*>::iterator iter1End = m_CollisionList.end();

		for (; iter1 != iter1End; ++iter1)
		{
			Collision(*iter, *iter1, fDeltaTime);
		}

	}




	m_CollisionList.clear();
}

bool CCollisionManager::Collision(CObj* pSrc, CObj* pDest, float fDeltaTime)
{
	const list<CCollider*>* pSrcList = pSrc->GetColliderList();
	const list<CCollider*>* pDestList = pDest->GetColliderList();

	list<CCollider*>::const_iterator iterSrc;
	list<CCollider*>::const_iterator iterSrcEnd = pSrcList->end();

	list<CCollider*>::const_iterator iterDest;
	list<CCollider*>::const_iterator iterDestEnd = pDestList->end();

	bool bCollision = false;


	for (iterSrc = pSrcList->begin(); iterSrc != iterSrcEnd; ++iterSrc)
	{
		for (iterDest = pDestList->begin(); iterDest != iterDestEnd; ++iterDest)
		{
			if ((*iterSrc)->Collision((*iterDest))) // ���� �浹�� �ǰ� �ִ��� Ȯ��
			{
				bCollision = true;
			
				(*iterDest)->SetHitPoint((*iterDest)->GetHitPoint());

				//ó�� �浹 ��
				if (!(*iterSrc)->CheckCollisionList(*iterDest))
				{
					(*iterSrc)->AddCollider(*iterDest);
					(*iterDest)->AddCollider(*iterSrc);

					(*iterSrc)->CallFunction(CS_ENTER, *iterDest, fDeltaTime);
					(*iterDest)->CallFunction(CS_ENTER, *iterSrc, fDeltaTime); 

				}
				else
				{
					//������ �浹�Ǿ� �����鼭 ���ݵ� �浹 ��
					(*iterSrc)->CallFunction(CS_STAY, *iterDest, fDeltaTime);
					(*iterDest)->CallFunction(CS_STAY, *iterSrc, fDeltaTime);

				}
			}
			else if((*iterSrc)->CheckCollisionList(*iterDest)) // ���� �浹�� ���� �����鼭 ������ �浹 ��Ͽ� �����Ƿ�, �浹���� ó�� ��� ����
			{
				(*iterSrc)->EraseCollisionList(*iterDest);
				(*iterDest)->EraseCollisionList(*iterSrc);

				(*iterSrc)->CallFunction(CS_LEAVE, *iterDest, fDeltaTime);
				(*iterDest)->CallFunction(CS_LEAVE, *iterSrc, fDeltaTime);

			}

			else
			{

			}
				
		}
	}

	return bCollision;
}
