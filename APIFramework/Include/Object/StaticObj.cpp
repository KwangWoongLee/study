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
}

int CStaticObj::Update(float fDeltaTime)
{
	return 0;
}

int CStaticObj::LateUpdate(float fDeltaTime)
{
	return 0;
}

void CStaticObj::Collision(float fDeltaTime)
{
}

void CStaticObj::Render(HDC hdc, float fDeltaTime)
{
}
