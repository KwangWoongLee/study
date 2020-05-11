#pragma once

#include "../Game.h"

class Scene
{
protected:
	friend class Scenemanager;

protected:
	list<class CLayer*> m_LayerList;

protected:
	Scene();
	virtual ~Scene() = 0;

public:
	class CLayer* CreateLayer(const string& strTag, int iZorder=0);
	class CLayer* FindLayer(const string& strTag);


public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hdc,float fDeltaTime);

public:
	static bool LayerSort(class CLayer* pL1, class CLayer* pL2);

};