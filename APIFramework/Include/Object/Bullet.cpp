#include "Bullet.h"
#include "../Resources/Texture.h"
#include "../Collider/ColliderSphere.h"


CBullet::CBullet()	:
	m_fDist(0.f),
	m_fLimitDist(500.f)
{

}

CBullet::CBullet(const CBullet& bullet)	:
	CMoveObj(bullet)
{
	m_fLimitDist = bullet.m_fLimitDist;
	m_fDist = bullet.m_fDist;

}

CBullet::~CBullet()
{
}


bool CBullet::Init()
{
	SetSpeed(500.f);
	SetPivot(0.5f, 0.25f);
	SetTexture("Bullet", L"bomb.bmp");

	//m_pTexture->SetColorKey(0, 248, 0);
	CColliderSphere* pSphere = AddCollider<CColliderSphere>("BulletBody");

	pSphere->SetSphere(POSITION(0.f,0.f),25.f);


	SAFE_RELEASE(pSphere);

	return true;
}

int CBullet::Update(float fDeltaTime)
{
	CMoveObj::Update(fDeltaTime);

	MoveAngle(fDeltaTime);

	m_fDist += GetSpeed() * fDeltaTime;

	if (m_fDist >= m_fLimitDist)
	{
		Die();
	}


	return 0;
}

int CBullet::LateUpdate(float fDeltaTime)
{
	CMoveObj::LateUpdate(fDeltaTime);
	return 0;
}

void CBullet::Collision(float fDeltaTime)
{
	CMoveObj::Collision(fDeltaTime);
}

void CBullet::Render(HDC hdc, float fDeltaTime)
{
	CMoveObj::Render(hdc, fDeltaTime);

}

CBullet* CBullet::Clone()
{
	return new CBullet(*this);
}

void CBullet::Hit(CCollider* pSrc, CCollider* pDest, float fDeltaTime)
{
	if (GetTag() == "PlayerBullet" && pDest->GetTag() == "MinionBody")
		Die();

	else if (GetTag() == "MinionBullet" && pDest->GetTag() == "PlayerBody")
		Die();
}
