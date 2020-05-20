#pragma once
#include "Collider.h"
class CColliderRect :
	public CCollider
{
protected:
	friend class CObj;

protected:
	CColliderRect();
	CColliderRect(const CColliderRect& coll);
	virtual ~CColliderRect();

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual bool Collision(CCollider* pDest);
	virtual void Render(HDC hDc, float fDeltaTime);
	virtual CColliderRect* Clone();


private:
	RECTANGLE m_tInfo;
	RECTANGLE m_tWolrdInfo;

public:
	void SetRect(float l, float t, float b, float r);
	
	RECTANGLE GetInfo() const
	{
		return m_tInfo;
	}

	RECTANGLE GetWorldInfo() const
	{
		return m_tWolrdInfo;
	}



};

