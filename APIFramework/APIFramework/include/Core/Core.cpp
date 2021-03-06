#include "Core.h"
#include "..\Scene\SceneManager.h"
#include "Timer.h"
CCore* CCore::m_pInst = nullptr;
bool CCore::m_bLoop = true;

CCore::CCore()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(238);
}
CCore::~CCore()
{
    DESTROY_SINGLE(CSceneManager);
    DESTROY_SINGLE(CTimer);
}

ATOM CCore::MyRegisterClass()
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = CCore::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = m_hInst;
    wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOWFRAME + 1);
    wcex.lpszMenuName = NULL;//MAKEINTRESOURCEW(IDC_DELTATIME);
    wcex.lpszClassName = L"APIFramework";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    return RegisterClassExW(&wcex);
}

BOOL CCore::Create()
{
   
    m_hWnd = CreateWindowW(L"APIFramework", L"APIFrameworkTest", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInst, nullptr);

    if (!m_hWnd)
    {
        return FALSE;
    }
    // 실제 윈도우 타이틀바나 메뉴를 포함한 윈도우의 크기를 구해준다.
    RECT rc = { 0,0, m_tRS.iWidth, m_tRS.iHeight };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    // 위에서 구해준 크기로 윈도우 클라이언트 영역의 크기를 원하는 크기로 맞춰줘야 한다.
    SetWindowPos(m_hWnd, HWND_TOPMOST, 100, 100, rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);

    ShowWindow(m_hWnd, SW_SHOW);
    UpdateWindow(m_hWnd);

    return TRUE;
}

void CCore::Logic()
{
    // 타이머 갱신
    GET_SINGLE(CTimer)->Update();

    float fDeltaTime = GET_SINGLE(CTimer)->GetDeltaTime();
    Input(fDeltaTime);
    Update(fDeltaTime);
    LateUpdate(fDeltaTime);
    Collision(fDeltaTime);
    Render(fDeltaTime);
}

void CCore::Input(float fDeltaTime)
{
    GET_SINGLE(CSceneManager)->Input(fDeltaTime);
}
int CCore::Update(float fDeltaTime)
{
    GET_SINGLE(CSceneManager)->Update(fDeltaTime);
    return 0;
}

int CCore::LateUpdate(float fDeltaTime)
{
    GET_SINGLE(CSceneManager)->LateUpdate(fDeltaTime);
    return 0;
}

void CCore::Collision(float fDeltaTime)
{
    GET_SINGLE(CSceneManager)->Collision(fDeltaTime);
}

void CCore::Render(float fDeltaTime)
{
    GET_SINGLE(CSceneManager)->Render(m_hDC, fDeltaTime);
}

bool CCore::Init(HINSTANCE hInstance)
{
	m_hInst = hInstance;
    MyRegisterClass();

    // 해상도 설정
    m_tRS.iWidth = 1280;
    m_tRS.iHeight = 720;

    Create();
    // 화면 DC를 만들어준다
    m_hDC = GetDC(m_hWnd);
    // 타이머 초기화
    if (!GET_SINGLE(CTimer)->Init())
        return false;
    // 장면 관리자 초기화
    if (!GET_SINGLE(CSceneManager)->Init())
        return false;
	return true;
}

int CCore::Run()
{
    MSG msg;
    
    // 기본 메시지 루프입니다:
    while (m_bLoop)
    {
        // PeekMesaage는 메시지가 메시지큐에 없어도 바로 빠진다
        // 메시지가 있을 경우 true, 없을 경우 false가 된다
        // 메시지가 없는 시간의 윈도우의 dead time 이다
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else // 윈도우 dead time 일때, 게임 구현부
        {
            Logic();
        }
    }
   
    return (int)msg.wParam;
}

LRESULT CCore::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_KEYDOWN: // 이 메시지가 들어올 경우 wParam에 어떤 키가 눌렸는지가 들어온다
    {
        switch (wParam)
        {
        case VK_ESCAPE:
        {
            DestroyWindow(hWnd);
            break;
        }
        }
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        m_bLoop = false;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
