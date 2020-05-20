#include "ColliderRect.h"
#include "../Object/Obj.h"
#include "ColliderSphere.h"
#include "ColliderPixel.h"

void CColliderRect::SetRect(float l, float t, float r, float b)
{
	m_tInfo.l = l;
	m_tInfo.r = r;
	m_tInfo.t = t;
	m_tInfo.b = b;
}

CColliderRect::CColliderRect()
{
	m_eCollType = CT_RECT;
}

CColliderRect::CColliderRect(const CColliderRect& coll)	:
	CCollider(coll)
{
	m_tInfo = coll.m_tInfo;
}

CColliderRect::~CColliderRect()
{

}

bool CColliderRect::Init()
{
	return true;
}

void CColliderRect::Input(float fDeltaTime)
{
	CCollider::Input(fDeltaTime);
}

int CColliderRect::Update(float fDeltaTime)
{
	CCollider::Update(fDeltaTime);
	return 0;
}

int CColliderRect::LateUpdate(float fDeltaTime)
{
	CCollider::LateUpdate(fDeltaTime);
	
	POSITION	t_Pos = m_pObj->GetPos();

	m_tWolrdInfo.l = t_Pos.x + m_tInfo.l;
	m_tWolrdInfo.t = t_Pos.y + m_tInfo.t;
	m_tWolrdInfo.r = t_Pos.x + m_tInfo.r;
	m_tWolrdInfo.b = t_Pos.y + m_tInfo.b;

	return 0;
}

bool CColliderRect::Collision(CCollider* pDest)
{
	switch (pDest->GetColliderType())
	{
	case CT_RECT:
		return CollisionRectToRect(m_tWolrdInfo, ((CColliderRect*)pDest)->GetWorldInfo());
	case CT_SPHERE:
		return CollisionRectToSphere(m_tWolrdInfo, ((CColliderSphere*)pDest)->GetWorldInfo());
	case CT_PIXEL:
		return CollisionRectToPixel(m_tWolrdInfo, ((CColliderPixel*)pDest)->GetPixel(),((CColliderPixel*)pDest)->GetWidth(), ((CColliderPixel*)pDest)->GetHeight());
	}
	return false;

}

void CColliderRect::Render(HDC hDc, float fDeltaTime)
{
	CCollider::Render(hDc,fDeltaTime);
}

CColliderRect* CColliderRect::Clone()
{
	return new CColliderRect(*this);
}
