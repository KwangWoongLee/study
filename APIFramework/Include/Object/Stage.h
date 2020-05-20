#pragma once
#include "StaticObj.h"

class CStage :
	public CStaticObj
{
private:
	friend class CObj;
	friend class Scene;

private:
	CStage();
	CStage(const CStage& bullet);
	~CStage();


public:

	virtual bool Init();
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hdc, float fDeltaTime);
	virtual CStage* Clone();

};

