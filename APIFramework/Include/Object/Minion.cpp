#include "Minion.h"
#include "../Core.h"
#include "../Resources/Texture.h"
#include "../Collider/ColliderRect.h"
#include "Bullet.h"
CMinion::CMinion()	:
	m_fFireTime(0.f),
	m_fFireLimitTime(3.f)
{
}

CMinion::CMinion(const CMinion& minion) :
	CMoveObj(minion)
{
	m_eDir = minion.m_eDir;
	m_fFireTime = minion.m_fFireTime;
	m_fFireLimitTime = minion.m_fFireLimitTime;

}


CMinion::~CMinion()
{

}

bool CMinion::Init()
{
	SetSize(100.f, 100.f);
	SetPos(800.f, 100.f);
	SetSpeed(400.f);
	SetPivot(0.5f, 0.5f);

	SetTexture("Minion", L"minion.bmp");

	m_pTexture->SetColorKey(25, 51, 126);


	m_eDir = MD_FRONT;

	CColliderRect* pRC = AddCollider<CColliderRect>("MinionBody");

	pRC->SetRect(-50.f, -50.f, 50.f, 50.f);
	pRC->AddCollisionFunction(CS_ENTER, this,
		&CMinion::CollisionBullet);

	SAFE_RELEASE(pRC);


	return true;
}

int CMinion::Update(float fDeltaTime)
{
	CMoveObj::Update(fDeltaTime);
	MoveYFromSpeed(fDeltaTime, m_eDir);

	if (m_tPos.y + m_tSize.y >= GET_RESOLUTION.iH)
	{ 
		m_tPos.y = GET_RESOLUTION.iH - m_tSize.y;
		m_eDir = MD_BACK;
	}
	else if (m_tPos.y <= 0)
	{
		m_tPos.y = 0.f;
		m_eDir = MD_FRONT;
	}

	m_fFireTime += fDeltaTime;

	if (m_fFireTime >= m_fFireLimitTime)
	{
		m_fFireTime = 0.f;
		Fire();
	}

	return 0;
}

int CMinion::LateUpdate(float fDeltaTime)
{
	CMoveObj::LateUpdate(fDeltaTime);
	return 0;
}

void CMinion::Collision(float fDeltaTime)
{
	CMoveObj::Collision(fDeltaTime);
}

void CMinion::Render(HDC hdc, float fDeltaTime)
{
	CMoveObj::Render(hdc, fDeltaTime);
}

CMinion* CMinion::Clone()
{
	return new CMinion(*this);
}

void CMinion::CollisionBullet(CCollider* pSrc, CCollider* pDest, float fDeltaTime)
{
	if (pDest->GetObj()->GetTag() == "PlayerBullet")
		Die();
}

void CMinion::Fire()
{
	CObj* pBullet = CObj::CreateCloneObj("Bullet", "MinionBullet", m_pLayer);

	((CMoveObj*)pBullet)->SetAngle(PI);
	pBullet->AddCollisionFunction("BulletBody", CS_ENTER, (CBullet*)pBullet, &CBullet::Hit);

	float x = GetLeft() - pBullet->GetSize().x * (1.f - pBullet->GetPivot().x);
	float y = GetCenter().y;

	pBullet->SetPos(x,y);

	SAFE_RELEASE(pBullet);

}
