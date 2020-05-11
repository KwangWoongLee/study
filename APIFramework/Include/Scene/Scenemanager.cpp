#include "Scenemanager.h"
#include "InGameScene.h"

DEFINITION_SINGLE(Scenemanager)

Scenemanager::Scenemanager()	:
	m_pScene(NULL),
	m_pNextScene(NULL)

{
	
}

Scenemanager::~Scenemanager()
{
	SAFE_DELETE(m_pScene);
}

bool Scenemanager::Init() 
{
	CreateScene<InGameScene>(SC_CURRENT);

	return true;
}

void Scenemanager::Input(float fDeltaTime)
{
	m_pScene->Input(fDeltaTime);
}



int Scenemanager::Update(float fDeltaTime)
{
	m_pScene->Update(fDeltaTime);
	return 0;
}



int Scenemanager::LateUpdate(float fDeltaTime)
{
	m_pScene->LateUpdate(fDeltaTime);
	return 0;
}



void Scenemanager::Collision(float fDeltaTime)
{
	m_pScene->Collision(fDeltaTime);
}

void Scenemanager::Render(HDC hdc, float fDeltaTime)
{
	m_pScene->Render(hdc,fDeltaTime);
}


