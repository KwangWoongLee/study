#include "Stage.h"
#include "../Resources/Texture.h"
#include "../Core.h"
#include "../Core/Camera.h"


CStage::CStage()
{

}

CStage::CStage(const CStage& stage) :
	CStaticObj(stage)
{

}

CStage::~CStage()
{

}

bool CStage::Init()
{
	SetPos(0.f, 0.f);
	SetSize(1500.f, 1200.f);
	SetPivot(0.f, 0.f);

	SetTexture("Stage", L"Stage.bmp");
	return true;
}
int CStage::Update(float fDeltaTime)
{
	CStaticObj::Update(fDeltaTime);
	return 0;
}

int CStage::LateUpdate(float fDeltaTime)
{
	CStaticObj::LateUpdate(fDeltaTime);
	return 0;
}

void CStage::Collision(float fDeltaTime)
{
	CStaticObj::Collision(fDeltaTime);
}

void CStage::Render(HDC hdc, float fDeltaTime)
{
	//CStaticObj::Render(hdc, fDeltaTime);
	if (m_pTexture)
	{
		POSITION	tPos = m_tPos - m_tSize * m_tPivot;
		POSITION	tCamPos = GET_SINGLE(CCamera)->GetPos();


		BitBlt(hdc, tPos.x, tPos.y, GET_RESOLUTION.iW, GET_RESOLUTION.iH, m_pTexture->GetDC(), tCamPos.x, tCamPos.y, SRCCOPY);
	}

}

CStage* CStage::Clone()
{
	return new CStage(*this);
}
