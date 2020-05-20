#pragma once

#include "../Game.h"

class Scene
{
protected:
	friend class Scenemanager;

private:
	static unordered_map<string, class CObj*> m_mapPrototype;
	bool m_bLife;
	bool m_bEnable;

protected:
	list<class CLayer*> m_LayerList;

protected:
	Scene();
	virtual ~Scene() = 0;


public:
	static void ErasePrototype(const string& strTag);
	static void ErasePrototype();
	template <typename T>
	static typename T* CreatePrototype(const string& strTag)
	{
		T* pObj = new T;

		pObj->SetTag(strTag);

		if (!pObj->Init())
		{
			SAFE_RELEASE(pObj);
			return NULL;
		}

		pObj->AddRef();
		m_mapPrototype.insert(make_pair(strTag, pObj));

		return pObj;
	}

public:
	static CObj* FindPrototype(const string& strKey);

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