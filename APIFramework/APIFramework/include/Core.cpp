#include "Core.h"
#include "Scene\SceneManager.h"
#include "Core\Timer.h"
CCore* CCore::m_pInst = nullptr;
bool CCore::m_bLoop = true;

CCore::CCore()
{

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
    // ���� ������ Ÿ��Ʋ�ٳ� �޴��� ������ �������� ũ�⸦ �����ش�.
    RECT rc = { 0,0, m_tRS.iWidth, m_tRS.iHeight };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    // ������ ������ ũ��� ������ Ŭ���̾�Ʈ ������ ũ�⸦ ���ϴ� ũ��� ������� �Ѵ�.
    SetWindowPos(m_hWnd, HWND_TOPMOST, 100, 100, rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);

    ShowWindow(m_hWnd, SW_SHOW);
    UpdateWindow(m_hWnd);

    return TRUE;
}

void CCore::Logic()
{
    // Ÿ�̸� ����
    GET_SINGLE(CTimer)->Update();

    float fDeltaTime = GET_SINGLE(CTimer)->GetDeltaTime();
    Input(fDeltaTime);
    Update(fDeltaTime);
    LateUpdate(fDeltaTime);
    Collision(fDeltaTime);
    Render(hDC, fDeltaTime);
}

void CCore::Input(float fDeltaTime)
{
    GET_SINGLE(CSceneManager)->Input(fDeltaTime);
}
int CCore::Update(float fDeltaTime)
{
    GET_SINGLE(CSceneManager)->Update(fDeltaTime);
}

int CCore::LateUpdate(float fDeltaTime)
{
    GET_SINGLE(CSceneManager)->LateUpdate(fDeltaTime);
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

    // �ػ� ����
    m_tRS.iWidth = 1280;
    m_tRS.iHeight = 720;

    Create();
    // ȭ�� DC�� ������ش�
    m_hDC = GetDC(m_hWnd);
    // Ÿ�̸� �ʱ�ȭ
    if (!GET_SINGLE(CTimer)->Init())
        return false;
    // ��� ������ �ʱ�ȭ
    if (!GET_SINGLE(CSceneManager)->Init())
        return false;
	return true;
}

int CCore::Run()
{
    MSG msg;
    
    // �⺻ �޽��� �����Դϴ�:
    while (m_bLoop)
    {
        // PeekMesaage�� �޽����� �޽���ť�� ��� �ٷ� ������
        // �޽����� ���� ��� true, ���� ��� false�� �ȴ�
        // �޽����� ���� �ð��� �������� dead time �̴�
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else // ������ dead time �϶�, ���� ������
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
    case WM_KEYDOWN: // �� �޽����� ���� ��� wParam�� � Ű�� ���ȴ����� ���´�
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
        // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
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
