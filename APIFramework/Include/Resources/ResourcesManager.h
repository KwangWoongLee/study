#pragma once

#include "../Game.h"

class CResourcesManager
{
private:
	unordered_map<string, class CTexture*>	m_mapTexture;
	HINSTANCE m_hInst;
	HDC		m_hdc;
	class CTexture* pBackBuffer;
	

public:
	bool Init(HINSTANCE hInst, HDC hdc);

	class CTexture* GetBackBuffer()	const;

	class CTexture* LoadTexture(const string& strKey,
		const wchar_t* pFileName, const string& strPathKey);

	class CTexture* FindTexture(const string& strKey);

	DECLARE_SINGLE(CResourcesManager);

};

