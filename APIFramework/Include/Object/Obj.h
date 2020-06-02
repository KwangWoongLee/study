#pragma once

#include "../Core/Ref.h"
#include "../Scene/Layer.h"
#include "../Collider/Collider.h"

class CObj :
	public CRef
{
protected:
	friend class Scene;
	
protected:
	CObj();
	CObj(const CObj& obj);
	virtual ~CObj();


private:
	static list<CObj*>	m_ObjList;
	

public:
	static void AddObj(CObj* obj);
	static CObj* FindObject(const string& strTag);
	static void EraseObj(CObj* pObj);
	static void EraseObj(const string& strTag);
	static void EraseObj();


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
	bool	m_bIsPhysics;
	float	m_fGravityTime;

public:
	

	void ClearGravity() 
	{
		m_fGravityTime = 0.f;
	}

	void SetPhysics(bool bPhysics)
	{
		m_bIsPhysics = bPhysics;
	}

	bool GetPhysics() const
	{
		return m_bIsPhysics;
	}

protected:
	string		m_strTag;
	POSITION	m_tPos;
	_SIZE		m_tSize;
	_SIZE		m_tImageOffset;
	POSITION	m_tPivot;
	float		m_fAngle;	
	class CTexture* m_pTexture;
	list<CCollider*> m_ColliderList; 
	class CAnimation* m_pAnimation;

public:
	class CAnimation* CreateAnimation(const string& strTag);

	bool AddAnimationClip(const string& strTag, ANIMATION_TYPE eType,
		ANIMATION_OPTION eOption, float fAnimationLimitTime,
		int iFrameMaxX, int iFrameMaxY, int iStartX, int iStartY,
		int iLengthX, int iLengthY, float fOptionLimitTime,
		const string& strTexKey, const wchar_t* pFileName,
		const string& strPathKey = TEXTURE_PATH);

	bool AddAnimationClip(const string& strTag, ANIMATION_TYPE eType,
		ANIMATION_OPTION eOption, float fAnimationLimitTime,
		int iFrameMaxX, int iFrameMaxY, int iStartX, int iStartY,
		int iLengthX, int iLengthY, float fOptionLimitTime,
		const string& strTexKey, const vector<wstring>& vecFileName,
		const string& strPathKey = TEXTURE_PATH);


	const list<CCollider*>* GetColliderList() const
	{
		return &m_ColliderList;
	}

public:
	template<typename T>
	void AddCollisionFunction(const string& strTag, COLLISION_STATE eState, T* pObj,
		void (T::* pFunc)(CCollider*, CCollider*, float))
	{
		list<CCollider*>::iterator iter;
		list<CCollider*>::iterator iterEnd = m_ColliderList.end();

		for (iter = m_ColliderList.begin(); iter != iterEnd; ++iter)
		{
			if ((*iter)->GetTag() == strTag)
			{
				(*iter)->AddCollisionFunction(eState, pObj, pFunc);
				break;
			}
		}

	}


public:
	template <typename T>
	T* AddCollider(const string& strTag)
	{
		T* pCollider = new T;

		pCollider->SetObj(this);
		pCollider->SetTag(strTag);

		if (!pCollider->Init())
		{
			SAFE_RELEASE(pCollider);
			return NULL;
		}

		pCollider->AddRef();
		m_ColliderList.push_back(pCollider);

		return pCollider;

	}


	bool CheckCollider()
	{
		return !m_ColliderList.empty();
	}

public:
	float GetLeft() const
	{
		return m_tPos.x - m_tSize.x*m_tPivot.x;
	}

	float GetRight() const
	{
		return GetLeft() + m_tSize.x;
	}

	float GetTop() const
	{
		return m_tPos.y - m_tSize.y * m_tPivot.y;
	}

	float GetBottom() const
	{
		return GetTop() + m_tSize.y;
	}

	POSITION GetCenter() const
	{
		return POSITION(GetLeft() + m_tSize.x / 2.f, GetTop() + m_tSize.y / 2.f);
	}

	POSITION GetPivot() const
	{
		return m_tPivot;
	}

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
	void SetImageOffset(const _SIZE& tOffset)
	{
		m_tImageOffset = tOffset;
	}

	void SetImageOffset(float x, float y)
	{
		m_tImageOffset.x = x;
		m_tImageOffset.y = y;

	}


	void SetPivot(float x, float y)
	{
		m_tPivot.x = x;
		m_tPivot.y = y;
	}
	void SetPivot(const POSITION& pivot)
	{
		m_tPivot.x = pivot.x;
		m_tPivot.y = pivot.y;
	}


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
	void SetTexture(class CTexture* pTexture);
	void SetTexture(const string& strKey,
		const wchar_t* pFileName = NULL,
		const string& strPathKey = TEXTURE_PATH);
	void SetColorKey(unsigned char r, unsigned char g, unsigned char b);
	void SetAnimationClipColorKey(const string& strClip, unsigned char r, unsigned char g, unsigned char b);

public:
	virtual bool Init() = 0;
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDc, float fDeltaTime);
	virtual CObj* Clone() = 0;


public:
	template <typename T>
	static typename T* CreateObj(const string& strTag, class CLayer* pLayer =NULL)
	{
		T* pObj = new T;

		pObj->SetTag(strTag);

		if (!pObj->Init())
		{
			SAFE_RELEASE(pObj);
			return NULL;
		}

		if (pLayer)
		{
			pLayer->AddObject(pObj);
		}

		AddObj(pObj);

		return pObj;
	}




	static CObj* CreateCloneObj(const string& strPrototypeKey, const string& strTag, class CLayer* pLayer);



};

