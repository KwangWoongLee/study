#pragma once
#include "../Game.h"

class CTimer
{
private:
	HWND			m_hWnd;
	LARGE_INTEGER m_tSecond;
	LARGE_INTEGER m_tTime;
	float		m_fDeltaTime;
	float		m_fFPSTime;
	float		m_fFPS;
	float		m_fTimeScale;
	int			m_iFrameMax;
	int			m_iFrame;

public:
	void SetTimeScale(const float ts)
	{
		m_fTimeScale = ts;
	}

public:
	float GetDeltaTime()	const
	{
		return m_fDeltaTime * m_fTimeScale;

	}

	float GetFPS()	const
	{
		return m_fFPS;
	}

	float GetTimeScale() const
	{
		return m_fTimeScale;
	}


public:
	bool Init(HWND hWnd);
	void Update();

	DECLARE_SINGLE(CTimer);

};

