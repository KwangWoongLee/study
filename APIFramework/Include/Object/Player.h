#pragma once
#include "MoveObj.h"
class CPlayer :
	public CMoveObj
{

private:
	friend class CObj;
	friend class Scene;

private:
	CPlayer();
	CPlayer(const CPlayer& player); 
	~CPlayer();

private:
	bool m_bAttack;
	int m_iDir;


public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hdc, float fDeltaTime);
	virtual CPlayer* Clone();

public:
	void Hit(class CCollider* pSrc,
		class CCollider* pDest, float fDeltaTime);

	void HitStay(class CCollider* pSrc,
		class CCollider* pDest, float fDeltaTime);


private:
	void Fire();
	void PutBomb();


};

