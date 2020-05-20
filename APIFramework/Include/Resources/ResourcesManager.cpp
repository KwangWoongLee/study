#include "ResourcesManager.h"
#include "Texture.h"


DEFINITION_SINGLE(CResourcesManager)

CResourcesManager::CResourcesManager()
{
}


CResourcesManager::~CResourcesManager()
{
	SAFE_RELEASE(pBackBuffer);
	Safe_Release_Map(m_mapTexture);
}

bool CResourcesManager::Init(HINSTANCE hInst,HDC hdc)
{
	m_hInst = hInst;
	m_hdc = hdc;

	//백버퍼를 불러온다.
	pBackBuffer = LoadTexture("BackBuffer",L"BackBuffer.bmp",TEXTURE_PATH);

	return true;
}

CTexture* CResourcesManager::GetBackBuffer() const
{
	pBackBuffer->AddRef();
	return pBackBuffer;

}

CTexture* CResourcesManager::LoadTexture(const string& strKey, const wchar_t* pFileName, const string& strPathKey)
{
	CTexture* pTexture = FindTexture(strKey);

	if (pTexture)
		return pTexture;

	pTexture = new CTexture;

	if (!pTexture->LoadTexture(m_hInst, m_hdc,strKey,pFileName, strPathKey))
	{
		SAFE_RELEASE(pTexture);
		return NULL;

	}

	pTexture->AddRef();
	m_mapTexture.insert(make_pair(strKey, pTexture));

	return pTexture;


}

CTexture* CResourcesManager::FindTexture(const string& strKey)
{
	unordered_map<string, class CTexture*>::iterator iter = m_mapTexture.find(strKey);

	if (iter == m_mapTexture.end())
		return NULL;

	iter->second->AddRef();	

	return iter->second;
}
