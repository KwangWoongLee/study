#include "InGameScene.h"
#include "../Object/Player.h"
#include "../Object/Minion.h"
#include "Layer.h"

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


	SAFE_RELEASE(pPlayer);

	CMinion* pMinion = CObj::CreateObj<CMinion>("Minion", pLayer);

	SAFE_RELEASE(pMinion);

	return true;
}