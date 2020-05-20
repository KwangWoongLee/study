#include "Player.h"
#include "../Core/Input.h"
#include "../Object/Bullet.h"
#include "../Object/Bomb.h"
#include "../Collider/ColliderRect.h"
#include "../Animation/Animation.h"
CPlayer::CPlayer()
{
}

CPlayer::CPlayer(const CPlayer& player)	:
	CMoveObj(player)
{
		
}


CPlayer::~CPlayer()
{

}

bool CPlayer::Init()
{
	m_iDir = 0;
	SetSize(100.f, 100.f);
	SetPos(50.f, 50.f);
	SetSpeed(400.f);
	SetPivot(0.5f,0.5f);

	SetTexture("Player", L"HDS.bmp");
	SetColorKey(255, 255, 255);

	CColliderRect* pRC = AddCollider<CColliderRect>("PlayerBody");

	pRC->SetRect(-50.f, -50.f, 50.f, 50.f);
	pRC->AddCollisionFunction(CS_ENTER, this,
		&CPlayer::Hit);

	pRC->AddCollisionFunction(CS_STAY, this,&CPlayer::HitStay);

	SAFE_RELEASE(pRC);

	SetPhysics(true);

	CAnimation* pAni = CreateAnimation("PlayerAnimation");



	AddAnimationClip("IdleFront", AT_ATLAS, AO_ONCE_RETURN, 0.1f, 1, 1,
		0, 0, 1, 1, 0.f, "PlayerIdleFront", L"Player/Idle/Front/bazzi_front2.bmp");

	AddAnimationClip("IdleBack", AT_ATLAS, AO_ONCE_RETURN, 0.1f, 1, 1,
		0, 0, 1, 1, 0.f, "PlayerIdleBack", L"Player/Idle/Back/bazzi_back1.bmp");

	AddAnimationClip("IdleRight", AT_ATLAS, AO_ONCE_RETURN, 0.1f, 1, 1,
		0, 0, 1, 1, 0.f, "PlayerIdleRight", L"Player/Idle/Right/bazzi_right1.bmp");

	AddAnimationClip("IdleLeft", AT_ATLAS, AO_ONCE_RETURN, 0.1f, 1, 1,
		0, 0, 1, 1, 0.f, "PlayerIdleLeft", L"Player/Idle/Left/bazzi_left1.bmp");

	vector<wstring> vecFileName;

	for (int i = 1; i < 3; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Player/Run/Down/bazzi_down%d.bmp", i);
		vecFileName.push_back(strFileName);

	}

	AddAnimationClip("RunDown", AT_FRAME, AO_ONCE_RETURN, 1.f, 2, 1,
		0, 0, 2, 1, 0.f, "PlayerRunDown", vecFileName);

	vecFileName.clear();

	for (int i = 1; i < 3; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Player/Run/Up/bazzi_up%d.bmp", i);
		vecFileName.push_back(strFileName);

	}

	AddAnimationClip("RunUp", AT_FRAME, AO_ONCE_RETURN, 1.f, 2, 1,
		0, 0, 2, 1, 0.f, "PlayerRunUp", vecFileName);
	//SetAnimationClipColorKey("IdleRight", 19, 17, 19);

	vecFileName.clear();

	for (int i = 1; i < 4; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Player/Run/Right/bazzi_right%d.bmp", i);
		vecFileName.push_back(strFileName);

	}

	AddAnimationClip("RunRight", AT_FRAME, AO_ONCE_RETURN, 1.f, 3, 1,
		0, 0, 3, 1, 0.f, "PlayerRunRight", vecFileName);
	//SetAnimationClipColorKey("IdleRight", 19, 17, 19);

	vecFileName.clear();

	for (int i = 1; i < 3; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Player/Run/Left/bazzi_left%d.bmp", i);
		vecFileName.push_back(strFileName);

	}

	AddAnimationClip("RunLeft", AT_FRAME, AO_ONCE_RETURN, 1.f, 2, 1,
		0, 0, 2, 1, 0.f, "PlayerRunLeft", vecFileName);
	//SetAnimationClipColorKey("IdleRight", 19, 17, 19);

	SAFE_RELEASE(pAni);
	
	return true;
}

void CPlayer::Input(float fDeltaTime)
{
	CMoveObj::Input(fDeltaTime);


	if (KEYPRESS("MoveFront"))
	{
		MoveYFromSpeed(fDeltaTime, MD_BACK);
		m_pAnimation->ChangeClip("RunUp");
		m_iDir = 3;
	}

	if (KEYPRESS("MoveBack"))
	{
		MoveYFromSpeed(fDeltaTime, MD_FRONT);
		m_pAnimation->ChangeClip("RunDown");
		m_iDir = 4;
	}

	if (KEYPRESS("MoveLeft"))
	{
		MoveXFromSpeed(fDeltaTime, MD_BACK);
		m_pAnimation->ChangeClip("RunLeft");
		m_iDir = 2;
	}

	if (KEYPRESS("MoveRight"))
	{
		MoveXFromSpeed(fDeltaTime, MD_FRONT);
		m_pAnimation->ChangeClip("RunRight");
		m_iDir = 1;

	}

	if (KEYDOWN("PutBomb"))
	{
		PutBomb();
	}

}

int CPlayer::Update(float fDeltaTime)
{
	CMoveObj::Update(fDeltaTime);
	if (!m_bMove)
		switch (m_iDir)
		{
		case (1):
//			m_pAnimation->SetDefaultClip("IdleRight");
			m_pAnimation->ChangeClip("IdleRight");

			break;
		case (2):
			//m_pAnimation->SetDefaultClip("IdleLeft");
			m_pAnimation->ChangeClip("IdleLeft");

			break;
		case (3):
			//m_pAnimation->SetDefaultClip("IdleBack");
			m_pAnimation->ChangeClip("IdleBack");

			break;
		case (4):
			m_pAnimation->ChangeClip("IdleFront");

//			m_pAnimation->SetDefaultClip("IdleFront");
			break;
		}
	/*	if (m_bAttack && m_pAnimation->GetMotionEnd())
		m_bAttack = false;

	if (!m_bMove && !m_bAttack)
		m_pAnimation->ReturnClip();
	*/
	return 0;
}

int CPlayer::LateUpdate(float fDeltaTime)
{
	CMoveObj::LateUpdate(fDeltaTime);
	return 0;
}

void CPlayer::Collision(float fDeltaTime)
{
	CMoveObj::Collision(fDeltaTime);
}

void CPlayer::Render(HDC hdc, float fDeltaTime)
{
	CMoveObj::Render(hdc, fDeltaTime);


	//Rectangle(hdc, m_tPos.x, m_tPos.y, m_tPos.x + m_tSize.x, m_tPos.y + m_tSize.y);
}

CPlayer* CPlayer::Clone()
{
	return new CPlayer(*this);
}

void CPlayer::Hit(CCollider* pSrc, CCollider* pDest, float fDeltaTime)
{
	if (pDest->GetObj()->GetTag() == "MinionBullet");
		//Die();

	else if (pDest->GetTag() == "StageColl")
	{
		ClearGravity();
	}
}

void CPlayer::HitStay(CCollider* pSrc, CCollider* pDest, float fDeltaTime)
{
	if (pDest->GetTag() == "StageColl")
	{
		ClearGravity();
		//m_tPos.y = pSrc->GetHitPoint().y - m_tPivot.y * m_tSize.y;
	}
}
	
void CPlayer::Fire()
{
	m_bAttack = true;
	CObj* pBullet = CObj::CreateCloneObj("Bullet", "PlayerBullet",m_pLayer);

	pBullet->AddCollisionFunction("BulletBody", CS_ENTER, (CBullet*)pBullet, &CBullet::Hit);
	
	POSITION tPos;
	tPos.x = GetRight() + pBullet->GetSize().x * pBullet->GetPivot().x;
	tPos.y = GetCenter().y;


	pBullet->SetPos(tPos);

	SAFE_RELEASE(pBullet);


}
void CPlayer::PutBomb()
{
	CObj* pBomb = CObj::CreateCloneObj("Bomb", "PlayerBomb", m_pLayer);
	pBomb->AddCollisionFunction("BombBody", CS_ENTER, (CBomb*)pBomb, &CBomb::Hit);

	POSITION tPos;
	tPos.x = GetCenter().x;
	tPos.y = GetCenter().y;


	pBomb->SetPos(tPos);

	SAFE_RELEASE(pBomb);


}
