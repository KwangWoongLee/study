#pragma once
#include "MoveObj.h"
class CBomb :
	public CMoveObj
{
private:
	friend class CObj;
	friend class Scene;

private:
	CBomb();
	CBomb(const CBomb& bullet);
	~CBomb();

private:
	float	m_fLimitDist;
	float	m_fDist;
	float	m_fLimitLifeTime;
	float	m_fLifeTime;
	bool	m_bLife;

private:
	void SetBulletDistance(float fDist)
	{
		m_fLimitDist = fDist;
	}

	void SetBombLife(float fLifeTime)
	{
		m_fLifeTime = fLifeTime;
	}

public:
	virtual bool Init();
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hdc, float fDeltaTime);
	virtual CBomb* Clone();


public:
	void Hit(class CCollider* pSrc,
		class CCollider* pDest, float fDeltaTime);
};

