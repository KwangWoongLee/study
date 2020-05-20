#include "Bomb.h"
#include "../Resources/Texture.h"
#include "../Collider/ColliderSphere.h"
#include "../Animation/Animation.h"


CBomb::CBomb() :
	m_fDist(0.f),
	m_fLimitDist(500.f)
{

}

CBomb::CBomb(const CBomb& bullet) :
	CMoveObj(bullet)
{
	m_fLimitDist = bullet.m_fLimitDist;
	m_fDist = bullet.m_fDist;

}

CBomb::~CBomb()
{
}


bool CBomb::Init()
{
	SetSpeed(0.f);
	SetPivot(0.5f, 0.25f);
	SetTexture("Bomb", L"Bomb/bomb.bmp");

	//m_pTexture->SetColorKey(0, 248, 0);
	CColliderSphere* pSphere = AddCollider<CColliderSphere>("BombBody");

	pSphere->SetSphere(POSITION(0.f, 0.f), 25.f);


	SAFE_RELEASE(pSphere);

	return true;
}

int CBomb::Update(float fDeltaTime)
{
	CMoveObj::Update(fDeltaTime);
	//m_pAnimation->ChangeClip("ActiveBomb");

	return 0;
}

int CBomb::LateUpdate(float fDeltaTime)
{
	CMoveObj::LateUpdate(fDeltaTime);
	return 0;
}

void CBomb::Collision(float fDeltaTime)
{
	CMoveObj::Collision(fDeltaTime);
}

void CBomb::Render(HDC hdc, float fDeltaTime)
{
	CMoveObj::Render(hdc, fDeltaTime);

}

CBomb* CBomb::Clone()
{
	return new CBomb(*this);
}

void CBomb::Hit(CCollider* pSrc, CCollider* pDest, float fDeltaTime)
{
//	if (GetTag() == "PlayerBullet" && pDest->GetTag() == "MinionBody")
	//	Die();

}
