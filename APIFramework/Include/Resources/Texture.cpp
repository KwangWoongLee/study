#include "Texture.h"
#include "../Core/PathManager.h"

void CTexture::SetColorKey(unsigned char r, unsigned char g, unsigned char b)
{
	m_ColorKey = RGB(r, g, b);
	m_bColorKeyEnable = true;
}

void CTexture::SetColorKey(COLORREF colorKey)
{
	m_ColorKey = colorKey;
	m_bColorKeyEnable = true;

}

CTexture::CTexture()	:
	m_hMemDC(NULL),
	m_bColorKeyEnable(false),
	m_ColorKey(RGB(255,0,255))
{
}


CTexture::~CTexture()
{
	// 기존에 저장되어 있던 도구로 다시 지정.
	SelectObject(m_hMemDC, m_hOldBitmap);

	//Bitmap을 지워준다.
	DeleteObject(m_hBitmap);

	//DC를 지워준다.
	DeleteDC(m_hMemDC);

}

bool CTexture::LoadTexture(HINSTANCE hInst, HDC hdc, const string& strKey, const wchar_t* pFileName, const string& strPathKey)
{
	//메모리 DC를 만들어준다.
	m_hMemDC = CreateCompatibleDC(hdc);
	
	//전체경로를 만들어준다.
	const wchar_t* pPath = GET_SINGLE(CPathManager)->FindPath(strPathKey);

	wstring strPath;

	if (pPath)
		strPath = pPath;

	strPath += pFileName;




	m_hBitmap = (HBITMAP)LoadImage(hInst, strPath.c_str(),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//위에서 만들어준 비트맵 도구를 DC에 저장한다.
	// 지정할 때 반환되는 값은 DC에 기본적으로 저장되어 있던 도구가 반환됨.

	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	GetObject(m_hBitmap, sizeof(m_tInfo), &m_tInfo);

	return true;
}
