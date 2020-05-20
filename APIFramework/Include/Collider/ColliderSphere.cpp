#include "ColliderSphere.h"
#include "../Object/Obj.h"
#include "ColliderRect.h"
#include "ColliderPixel.h"

CColliderSphere::CColliderSphere()
{
	m_eCollType = CT_SPHERE;
}

CColliderSphere::CColliderSphere(const CColliderSphere& coll) :
	CCollider(coll)
{
	m_tInfo = coll.m_tInfo;
}

CColliderSphere::~CColliderSphere()
{

}

bool CColliderSphere::Init()
{
	return true;
}

void CColliderSphere::Input(float fDeltaTime)
{
	CCollider::Input(fDeltaTime);
}

int CColliderSphere::Update(float fDeltaTime)
{
	CCollider::Update(fDeltaTime);
	return 0;
}

int CColliderSphere::LateUpdate(float fDeltaTime)
{
	CCollider::LateUpdate(fDeltaTime);

	POSITION	t_Pos = m_pObj->GetPos();

	m_tWorldInfo.tCenter = t_Pos + m_tInfo.tCenter;
	m_tWorldInfo.tRadius = m_tInfo.tRadius;

	return 0;
}

bool CColliderSphere::Collision(CCollider* pDest)
{
	switch (pDest->GetColliderType())
	{
	case CT_SPHERE:
		return CollisionSphereToSphere(m_tWorldInfo, ((CColliderSphere*) pDest)->GetWorldInfo());
	case CT_RECT:
		return CollisionRectToSphere(((CColliderRect*)pDest)->GetWorldInfo(), m_tWorldInfo);
	}
	return false;

}

void CColliderSphere::Render(HDC hDc, float fDeltaTime)
{
	CCollider::Render(hDc, fDeltaTime);
}

CColliderSphere* CColliderSphere::Clone()
{
	return new CColliderSphere(*this);
}
