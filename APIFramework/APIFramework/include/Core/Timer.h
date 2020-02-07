#pragma once
#include "../Game.h"
class CTimer
{
	DECLARE_SINGLE(CTimer)
private:
	LARGE_INTEGER m_tSecond;
	LARGE_INTEGER m_tTime;
	float m_fDeltaTime;
	float m_fFPS;
	float m_fFPSTime;
	float m_fTimeScale;

	int m_iFrameMax;
	int m_iFrame;

public: 
	
	bool Init();
	void Update();
	float GetDeltaTime() const
	{
		return m_fDeltaTime * m_fTimeScale;
	}
	float GetFPS() const
	{
		return m_fFPS;
	}
	float GetTimeScale() const
	{
		return m_fTimeScale;
	}
	void SetTimeScale(float fTimeScale)
	{
		m_fTimeScale = fTimeScale;
	}
	
};

