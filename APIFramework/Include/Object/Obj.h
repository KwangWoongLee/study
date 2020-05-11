#pragma once

#include "../Core/Ref.h"
#include "../Scene/Layer.h"

class CObj :
	public CRef
{

protected:
	CObj();
	CObj(const CObj& obj);
	virtual ~CObj();

protected:
	class Scene* m_pScene;
	class CLayer* m_pLayer;

public:
	void SetScene(class Scene* pScene)
	{
		m_pScene = pScene;

	}
	void SetLayer(class CLayer* pLayer)
	{
		m_pLayer = pLayer;
	}
	class Scene* GetScene() const
	{
		return m_pScene;
	}
	class CLayer* GetLayer() const
	{
		return m_pLayer;
	}
protected:
	string		m_strTag;
	POSITION	m_tPos;
	_SIZE		m_tSize;
	POSITION	m_tPivot;
	float		m_fAngle;	


public:
	string GetTag() const
	{
		return m_strTag;
	}
	POSITION GetPos() const
	{
		return m_tPos;
	}
	_SIZE GetSize() const
	{
		return m_tSize;
	}

public:
	void SetTag(const string& strTag)
	{
		m_strTag = strTag;
	}

	void SetPos(const POSITION& pos)
	{
		m_tPos.x = pos.x;
		m_tPos.y = pos.y;
	}

	void SetPos(const POINT& pos)
	{
		m_tPos.x = pos.x;
		m_tPos.y = pos.y;
	}

	void SetPos(float x, float y)
	{
		m_tPos.x = x;
		m_tPos.y = y;
	}

	void SetSize(const _SIZE& tSize)
	{
		m_tSize.x = tSize.x;
		m_tSize.y = tSize.y;

	}

	void SetSize(float x, float y)
	{
		m_tSize.x = x;
		m_tSize.y = y;
	}

public:
	virtual bool Init() = 0;
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDc, float fDeltaTime);


public:
	template <typename T>
	static typename T* CreateObj(const string& strTag, class CLayer* pLayer =NULL)
	{
		T* pObj = new T;

		if (!pObj->Init())
		{
			SAFE_RELEASE(pObj);
			return NULL;
		}

		if (pLayer)
		{
			pLayer->AddObject(pObj);
		}


		return pObj;
	}

};

