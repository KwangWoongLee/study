#pragma once

#include "Game.h"
#include "Macro.h"

class Core
{
private:
	static Core* m_pInst;

public:
	static Core* GetInst()
	{
		if (!m_pInst) 
			m_pInst = new Core();
		return m_pInst;
	}
	static void DestroyInst()
	{
		SAFE_DELETE(m_pInst);
	}

private:
	Core();
	~Core();

private:
	static bool		m_bLoop;

private:
	HINSTANCE	m_hInst;
	HWND		m_hWnd;
	RESOLUTION	m_tRS;


public:
	bool Init(HINSTANCE hInst);
	int Run();

private:
	ATOM MyRegisterClass();
	BOOL Create();

public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

