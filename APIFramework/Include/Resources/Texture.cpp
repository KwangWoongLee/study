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
	// ������ ����Ǿ� �ִ� ������ �ٽ� ����.
	SelectObject(m_hMemDC, m_hOldBitmap);

	//Bitmap�� �����ش�.
	DeleteObject(m_hBitmap);

	//DC�� �����ش�.
	DeleteDC(m_hMemDC);

}

bool CTexture::LoadTexture(HINSTANCE hInst, HDC hdc, const string& strKey, const wchar_t* pFileName, const string& strPathKey)
{
	//�޸� DC�� ������ش�.
	m_hMemDC = CreateCompatibleDC(hdc);
	
	//��ü��θ� ������ش�.
	const wchar_t* pPath = GET_SINGLE(CPathManager)->FindPath(strPathKey);

	wstring strPath;

	if (pPath)
		strPath = pPath;

	strPath += pFileName;




	m_hBitmap = (HBITMAP)LoadImage(hInst, strPath.c_str(),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//������ ������� ��Ʈ�� ������ DC�� �����Ѵ�.
	// ������ �� ��ȯ�Ǵ� ���� DC�� �⺻������ ����Ǿ� �ִ� ������ ��ȯ��.

	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	GetObject(m_hBitmap, sizeof(m_tInfo), &m_tInfo);

	return true;
}