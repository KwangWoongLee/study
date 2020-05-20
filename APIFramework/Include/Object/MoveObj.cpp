#include "MoveObj.h"

CMoveObj::CMoveObj() :
	m_fAngle(0.f),
	m_fSpeed(100.f),
	m_bMove(false)

{
}

CMoveObj::CMoveObj(const CMoveObj& obj)	:
	CObj(obj)
{
	m_fAngle = obj.m_fAngle;
	m_fSpeed = obj.m_fSpeed;
	m_bMove = false;
}

CMoveObj::~CMoveObj()
{
}

void CMoveObj::Move(float x, float y)
{
	m_tPos.x += x;
	m_tPos.y += y;

	m_bMove = true;

}


void CMoveObj::Move(float x, float y, float fDeltaTime)
{
	m_tPos.x += x * fDeltaTime;
	m_tPos.y += y * fDeltaTime;

	m_bMove = true;
}

void CMoveObj::MoveX(float x)
{
	m_tPos.x += x;

	m_bMove = true;
}


void CMoveObj::MoveX(float x,float fDeltaTime)
{
	m_tPos.x += x * fDeltaTime;

	m_bMove = true;
}

void CMoveObj::MoveXFromSpeed(float fDeltaTime, MOVE_DIR eDir)
{
	m_tPos.x += m_fSpeed * fDeltaTime * eDir;

	m_bMove = true;
}

void CMoveObj::MoveYFromSpeed(float fDeltaTime, MOVE_DIR eDir)
{
	m_tPos.y += m_fSpeed * fDeltaTime * eDir;

	m_bMove = true;
}

void CMoveObj::MoveY(float y)
{
	m_tPos.y += y;
	m_bMove = true;

}


void CMoveObj::MoveY(float y, float fDeltaTime)
{
	m_tPos.y += y * fDeltaTime;
	m_bMove = true;

}

void CMoveObj::Move(const POSITION& tMove)
{
	m_tPos += tMove;
	m_bMove = true;
}

void CMoveObj::Move(const POSITION& tMove, float fDeltaTime)
{
	m_tPos += tMove * fDeltaTime;
	m_bMove = true;
}

void CMoveObj::MoveAngle()
{
	m_tPos.x += cosf(m_fAngle) * m_fSpeed;
	m_tPos.y += sinf(m_fAngle) * m_fSpeed;
	m_bMove = true;
}

void CMoveObj::MoveAngle(float fDeltaTime)
{
	m_tPos.x += cosf(m_fAngle) * m_fSpeed * fDeltaTime;
	m_tPos.y += sinf(m_fAngle) * m_fSpeed * fDeltaTime;
	m_bMove = true;
}

bool CMoveObj::Init()
{
	return true;
}

void CMoveObj::Input(float fDeltaTime)
{
	CObj::Input(fDeltaTime);

}

int CMoveObj::Update(float fDeltaTime)
{
	CObj::Update(fDeltaTime);

	return 0;
}

int CMoveObj::LateUpdate(float fDeltaTime)
{
	CObj::LateUpdate(fDeltaTime);

	return 0;
}

void CMoveObj::Collision(float fDeltaTime)
{
	CObj::Collision(fDeltaTime);

}

void CMoveObj::Render(HDC hdc, float fDeltaTime)
{
	CObj::Render(hdc, fDeltaTime);

	m_bMove = false;
}
