#include "StaticObj.h"


CStaticObj::CStaticObj()
{
}

CStaticObj::CStaticObj(const CStaticObj & sObj)	:
	CObj(sObj)
{
}

CStaticObj::~CStaticObj()
{

}
bool CStaticObj::Init()
{
	return true;
}

void CStaticObj::Input(float fDeltaTime)
{
	CObj::Input(fDeltaTime);
}

int CStaticObj::Update(float fDeltaTime)
{
	CObj::Update(fDeltaTime);
	return 0;
}

int CStaticObj::LateUpdate(float fDeltaTime)
{
	CObj::LateUpdate(fDeltaTime);
	return 0;
}

void CStaticObj::Collision(float fDeltaTime)
{
	CObj::Collision(fDeltaTime);
}

void CStaticObj::Render(HDC hdc, float fDeltaTime)
{
	CObj::Render(hdc, fDeltaTime);
}
