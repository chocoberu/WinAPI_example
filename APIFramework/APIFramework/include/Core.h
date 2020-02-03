#pragma once
#include "Game.h"

class CCore
{
private:
	CCore();
	~CCore();
	ATOM MyRegisterClass();
	BOOL Create();

	static CCore* m_pInst;
	HINSTANCE m_hInst;
	HWND m_hWnd;
	RESOLUTION m_tRS;
	static bool m_bLoop;
public:
	static CCore* GetInst()
	{
		if (!m_pInst)
			m_pInst = new CCore;
		return m_pInst;
	}
	static void DestroyInst()
	{
		SAFE_DELETE(m_pInst);
	}
	bool Init(HINSTANCE hInstance);
	int Run();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};