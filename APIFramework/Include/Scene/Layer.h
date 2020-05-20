#pragma once
#include "../Game.h"
 
class CLayer
{
private:
	friend class Scene;

private:
	CLayer();

public:
	~CLayer();

private:
	class Scene* m_pScene;

	string	m_strTag;
	int		m_iZOrder;
	list<class CObj*> m_ObjList;
	bool m_bLife;
	bool m_bEnable;

public:
	void SetEnable(bool bEnable)
	{
		m_bEnable = bEnable;
	}

	void Die()
	{
		m_bLife = false;
	}

	bool GetEnable() const
	{
		return m_bEnable;
	}

	bool GetLife()	const
	{
		return m_bLife;
	}

public:
	void SetTag(const string& strTag)
	{
		m_strTag = strTag;
	}

	void SetZOrder(int iZOrder)
	{
		m_iZOrder = iZOrder;
	}

	void SetScene(class Scene* pScene)
	{
		m_pScene = pScene;
	}

	string GetTag() const
	{
		return m_strTag;

	}

	int GetZOrder() const
	{
		return m_iZOrder;

	}

	Scene* GetScene() const
	{
		return m_pScene;
	}

public:
	void AddObject(class CObj* pObj);

public:
	void Input(float fDeltaTime);
	int Update(float fDeltaTime);
	int LateUpdate(float fDeltaTime);
	void Collision(float fDeltaTime);
	void Render(HDC hDc,float fDeltaTime);

};

