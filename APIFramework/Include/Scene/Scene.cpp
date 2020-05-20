
#include "Scene.h"
#include "Layer.h"
#include "../Object/Obj.h"

unordered_map<string, CObj*> Scene::m_mapPrototype;


Scene::Scene()
{
	CLayer* pLayer = CreateLayer("Default",1);
	pLayer = CreateLayer("UI", INT_MAX);
	pLayer = CreateLayer("Stage",0);

}
Scene::~Scene()
{
	Safe_Delete_VectorList(m_LayerList);
}

CLayer* Scene::CreateLayer(const string& strTag, int iZorder)
{
	CLayer* pLayer = new CLayer;

	pLayer->SetTag(strTag);
	pLayer->SetZOrder(iZorder);
	pLayer->SetScene(this);


	m_LayerList.push_back(pLayer);
	
	if (m_LayerList.size() >= 2)
		m_LayerList.sort(Scene::LayerSort);

	return pLayer;
}

CLayer* Scene::FindLayer(const string& strTag)
{

	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetTag() == strTag)
		{
			return *iter;
		}
	}
	return NULL;
}


void Scene::ErasePrototype()
{
	Safe_Release_Map(m_mapPrototype);
}

void Scene::ErasePrototype(const string& strTag)
{
	unordered_map<string, CObj*>::iterator iter = m_mapPrototype.find(strTag);

	if (!iter->second)
		return;

	SAFE_RELEASE(iter->second);
	m_mapPrototype.erase(iter);

}


bool Scene::Init()
{	 

	return true;
}


void Scene::Input(float fDeltaTime)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}


		(*iter)->Input(fDeltaTime);
		
		if (!(*iter)->GetLife())
		{
			SAFE_DELETE((*iter));
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
		}
		else
			++iter;

	}

}

int Scene::Update(float fDeltaTime)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}


		(*iter)->Update(fDeltaTime);

		if (!(*iter)->GetLife())
		{
			SAFE_DELETE((*iter));
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
		}
		else
			++iter;
	}
	return 0;
}

int Scene::LateUpdate(float fDeltaTime)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}


		(*iter)->LateUpdate(fDeltaTime);

		if (!(*iter)->GetLife())
		{
			SAFE_DELETE((*iter));
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
		}
		else
			++iter;
	}
	return 0;
}

void Scene::Collision(float fDeltaTime)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}


		(*iter)->Collision(fDeltaTime);

		if (!(*iter)->GetLife())
		{
			SAFE_DELETE((*iter));
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
		}
		else
			++iter;

	}
}

void Scene::Render(HDC hdc, float fDeltaTime)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Render(hdc,fDeltaTime);

		if (!(*iter)->GetLife())
		{
			SAFE_DELETE((*iter));
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
		}
		else
			++iter;

	}
}

bool Scene::LayerSort(CLayer* pL1, CLayer* pL2)
{
	return pL1->GetZOrder() < pL2->GetZOrder();
}

CObj* Scene::FindPrototype(const string& strKey)
{
	unordered_map<string, CObj*>::iterator iter = m_mapPrototype.find(strKey);

	if (iter == m_mapPrototype.end())
		return NULL;

	return iter->second;
}
