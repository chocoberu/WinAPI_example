#pragma once
#include "../Game.h"

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
	HDC m_hDC;
	RESOLUTION m_tRS;
	static bool m_bLoop;
	void Logic();
	void Input(float fDeltaTime);
	int Update(float fDeltaTime);
	int LateUpdate(float fDeltaTime);
	void Collision(float fDeltaTime);
	void Render(float fDeltaTime);

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
	RESOLUTION GetResoultion() const
	{
		return m_tRS;
	}
};