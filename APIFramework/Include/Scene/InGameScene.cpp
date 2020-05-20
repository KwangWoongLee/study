#include "InGameScene.h"
#include "../Object/Player.h"
#include "../Object/Minion.h"
#include "../Object/Bullet.h"
#include "../Object/Bomb.h"
#include "../Object/Stage.h"
#include "../Core/Camera.h"
#include "Layer.h"
#include "../Collider/ColliderPixel.h"

InGameScene::InGameScene()
{

}

InGameScene::~InGameScene()
{

}

bool InGameScene::Init()
{

	//부모  Scene클래스의 초기화
	if (!Scene::Init())
		return false;

	CLayer* pLayer = FindLayer("Default");

	CPlayer* pPlayer = CObj::CreateObj<CPlayer>("Player", pLayer);

	GET_SINGLE(CCamera)->SetTarget(pPlayer);

	SAFE_RELEASE(pPlayer);

	//CMinion* pMinion = CObj::CreateObj<CMinion>("Minion", pLayer);

	//SAFE_RELEASE(pMinion);

	//총알 프로토 타입을 만들어준다 .
	CBullet* pBullet = Scene::CreatePrototype<CBullet>("Bullet");
	
	pBullet->SetSize(100.f, 100.f);

	SAFE_RELEASE(pBullet);

	CBomb* pBomb = Scene::CreatePrototype<CBomb>("Bomb");

	pBomb->SetSize(100.f, 100.f);

	SAFE_RELEASE(pBomb);

	//
	CLayer* pStageLayer = FindLayer("Stage");

	CStage* pStage = CObj::CreateObj<CStage>("Stage", pStageLayer);

	CColliderPixel* pPixel = pStage->AddCollider<CColliderPixel>("StageColl");

	pPixel->SetPixelInfo("Stage.bmp");

	SAFE_RELEASE(pPixel);

	SAFE_RELEASE(pStage);


	return true;
}