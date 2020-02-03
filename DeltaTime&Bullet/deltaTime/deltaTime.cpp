// deltaTime.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "deltaTime.h"
#include <list>
#include <math.h>

using namespace std;
#define MAX_LOADSTRING 100

enum MOVE_DIR
{
    MD_BACK = -1,
    MD_NONE,
    MD_FRONT
};
typedef struct _tagRectangle
{
    float left, top, right, bottom;
} RECTANGLE, *PRECTANGLE;
typedef struct _tagSphere
{
    float x, y;
    float radius;
} SPHERE, *PSPHRER;

typedef struct _tagBullet
{
    SPHERE tSphere;
    float fDist;
    float fLimitDist;
} BULLET, *PBULLET;
typedef struct _tagMonster
{
    SPHERE tSphere;
    float fSpeed;
    float fTime;
    float fLimitTime;
    int iDir;
}MONSTER, * PMONSTER;

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND g_hWnd; // 윈도우 핸들
HDC g_hDC; // dc 핸들
bool g_bLoop = true;
RECTANGLE g_tPlayerRC = { 100,100, 200,200 }; // 플레이어
list<BULLET> g_PlayerBulletList; // 플레이어 총알
MONSTER g_tMonster;  // 몬스터
list<BULLET> g_MonsterBulletList; // 몬스터 총알

// 시간을 구하기 위한 변수들
LARGE_INTEGER g_tSecond;
LARGE_INTEGER g_tTime;
float g_fDeltaTime;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void Run(); // 함수 프로토타입

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DELTATIME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    g_hDC = GetDC(g_hWnd); // 화면용 DC 생성

    g_tMonster.tSphere.x = 700.f;
    g_tMonster.tSphere.y = 50.0f;
    g_tMonster.tSphere.radius = 50.0f;
    g_tMonster.fSpeed = 300.0f;
    g_tMonster.fTime = 0.0f;
    g_tMonster.fLimitTime = 1.3f;
    g_tMonster.iDir = MD_FRONT;

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DELTATIME));

    MSG msg;
    QueryPerformanceFrequency(&g_tSecond);
    QueryPerformanceCounter(&g_tTime);

    // 기본 메시지 루프입니다:
    while (g_bLoop)
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
            Run();
        }
    }
    ReleaseDC(g_hWnd, g_hDC);
    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DELTATIME));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOWFRAME +1);
    wcex.lpszMenuName = NULL;//MAKEINTRESOURCEW(IDC_DELTATIME);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }
   g_hWnd = hWnd; // 전역변수에 윈도우 핸들 설정
   // 실제 윈도우 타이틀바나 메뉴를 포함한 윈도우의 크기를 구해준다.
   RECT rc = { 0,0, 800,600 };
   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
   // 위에서 구해준 크기로 윈도우 클라이언트 영역의 크기를 원하는 크기로 맞춰줘야 한다.
   SetWindowPos(hWnd, HWND_TOPMOST, 100, 100, rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
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
        g_bLoop = false;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
void Run()
{
    // DeltaTime을 구해준다
    LARGE_INTEGER tTime;
    QueryPerformanceCounter(&tTime);

    g_fDeltaTime = (tTime.QuadPart - g_tTime.QuadPart) / static_cast<float>(g_tSecond.QuadPart);
    g_tTime = tTime;

    static float fTimeScale = 1.0f;
    if (GetAsyncKeyState(VK_F1) & 0x8000)
    {
        fTimeScale -= g_fDeltaTime;
        if (fTimeScale < 0.0f)
            fTimeScale = 0.0f;
    }
    if (GetAsyncKeyState(VK_F2) & 0x8000)
    {
        fTimeScale += g_fDeltaTime;
        if (fTimeScale > 1.0f)
            fTimeScale = 1.0f;
    }
    // 플레이어 초당 이동 속도 : 300
    float fSpeed = 300 * g_fDeltaTime * fTimeScale;
    
    RECT tempRect;
    GetClientRect(g_hWnd, &tempRect);
    if (GetAsyncKeyState('D') & 0x80000)
    {
        if (g_tPlayerRC.right < tempRect.right)
        {
            g_tPlayerRC.left += fSpeed;
            g_tPlayerRC.right += fSpeed;
            //InvalidateRect(g_hWnd, NULL, TRUE);
        }
    }
    if (GetAsyncKeyState('A') & 0x80000)
    {
        if (g_tPlayerRC.left > tempRect.left)
        {
            g_tPlayerRC.left -= fSpeed;
            g_tPlayerRC.right -= fSpeed;
            //InvalidateRect(g_hWnd, NULL, TRUE);
        }
    }
    if (GetAsyncKeyState('W') & 0x80000)
    {
        if (g_tPlayerRC.top > tempRect.top)
        {
            g_tPlayerRC.top -= fSpeed;
            g_tPlayerRC.bottom -= fSpeed;
            //InvalidateRect(g_hWnd, NULL, TRUE);
        }
    }
    if (GetAsyncKeyState('S') & 0x80000)
    {
        if (g_tPlayerRC.bottom < tempRect.bottom)
        {
            g_tPlayerRC.top += fSpeed;
            g_tPlayerRC.bottom += fSpeed;
            //InvalidateRect(g_hWnd, NULL, TRUE);
        }
    }
    if (GetAsyncKeyState(VK_SPACE) & 0x80000)
    {
        BULLET tBullet;

        tBullet.tSphere.x = g_tPlayerRC.right + 50;
        tBullet.tSphere.y = g_tPlayerRC.top + 50.0f;
        tBullet.tSphere.radius = 25.0f;
        
        tBullet.fDist = 0.0f;
        tBullet.fLimitDist = 600.0f;

        g_PlayerBulletList.push_back(tBullet);
    }

    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
    {
        POINT ptMouse;
        GetCursorPos(&ptMouse); // 마우스 커서 위치를 스크린 좌표로 얻어온다
        ScreenToClient(g_hWnd, &ptMouse); // 스크린 좌표를 클라이언트 좌표로 변환

        if (g_tPlayerRC.left <= ptMouse.x && ptMouse.x <= g_tPlayerRC.right &&
            g_tPlayerRC.top <= ptMouse.y && ptMouse.y <= g_tPlayerRC.bottom)
        {
            MessageBox(NULL, L"플레이어 클릭", L"마우스 클릭", MB_OK);
        }
        float fMX = g_tMonster.tSphere.x - ptMouse.x;
        float fMY = g_tMonster.tSphere.y - ptMouse.y;
        float fMDist = sqrtf(fMX * fMX + fMY * fMY);
        if (g_tMonster.tSphere.radius > fMDist)
        {
            MessageBox(NULL, L"몬스터 클릭", L"마우스 클릭", MB_OK);
        }
    }
    // 몬스터 이동
    g_tMonster.tSphere.y += g_tMonster.fSpeed * g_fDeltaTime * fTimeScale * g_tMonster.iDir;
    
    if (g_tMonster.tSphere.y + g_tMonster.tSphere.radius >= 600.0f)
    {
        g_tMonster.iDir = MD_BACK;
        g_tMonster.tSphere.y = 550.0f;
        
    }
    else if (g_tMonster.tSphere.y - g_tMonster.tSphere.radius <= 0.0f)
    {
        g_tMonster.iDir = MD_FRONT;
        g_tMonster.tSphere.y = 50.0f;
    }

    // 몬스터 총알 발사 로직
    g_tMonster.fTime += g_fDeltaTime * fTimeScale;
    
    if (g_tMonster.fTime >= g_tMonster.fLimitTime)
    {
        g_tMonster.fTime -= g_tMonster.fLimitTime;

        BULLET tBullet = {};

        tBullet.tSphere.x = g_tMonster.tSphere.x - g_tMonster.tSphere.radius - 25.0f;
        tBullet.tSphere.y = g_tMonster.tSphere.y;
        tBullet.tSphere.radius = 25.0f;

        tBullet.fDist = 0.0f;
        tBullet.fLimitDist = 600.0f;

        g_MonsterBulletList.push_back(tBullet);
    }

    // 플레이어 총알의 이동 처리
    float fBulletSpeed = 600.0f * g_fDeltaTime * fTimeScale;
    auto iterEnd = g_PlayerBulletList.end();
    for (auto iter = g_PlayerBulletList.begin(); iter != iterEnd;)
    {
        (*iter).tSphere.x += fBulletSpeed;
        (*iter).fDist += fBulletSpeed;
        
        // 플레이어 총알 대 몬스터 충돌
        float fX = (*iter).tSphere.x - g_tMonster.tSphere.x;
        float fY = (*iter).tSphere.y - g_tMonster.tSphere.y;
        float fDist = sqrtf(fX * fX + fY * fY);

        if (fDist <= (*iter).tSphere.radius + g_tMonster.tSphere.radius)
        {
            iter = g_PlayerBulletList.erase(iter);
            iterEnd = g_PlayerBulletList.end();
        }

        else if ((*iter).fDist >= (*iter).fLimitDist)
        {
            iter = g_PlayerBulletList.erase(iter);
            iterEnd = g_PlayerBulletList.end();
        }
        else if ((*iter).tSphere.x - (*iter).tSphere.radius > 800)
        {
            iter = g_PlayerBulletList.erase(iter);
            iterEnd = g_PlayerBulletList.end();
            
        }
        
        else
            iter++;
    }

    // 몬스터 총알 이동
    iterEnd = g_MonsterBulletList.end();
    for (auto iter = g_MonsterBulletList.begin(); iter != iterEnd;)
    {
        (*iter).tSphere.x -= fBulletSpeed;
        (*iter).fDist += fBulletSpeed;


        if ((*iter).fDist >= (*iter).fLimitDist)
        {
            iter = g_MonsterBulletList.erase(iter);
            iterEnd = g_MonsterBulletList.end();
        }
        else if ((*iter).tSphere.x - (*iter).tSphere.radius < 0.0f )
        {
            iter = g_MonsterBulletList.erase(iter);
            iterEnd = g_MonsterBulletList.end();

        }
        // 총알의 충돌처리 (사각형)
        /*else if (g_tPlayerRC.left <= (*iter).rc.right && (*iter).rc.left <= g_tPlayerRC.right
            && g_tPlayerRC.top <= (*iter).rc.bottom && (*iter).rc.top <= g_tPlayerRC.bottom)
        {
            iter = g_MonsterBulletList.erase(iter);
            iterEnd = g_MonsterBulletList.end();
        }*/
        else
        {
            iter++;
        }
    }
    
    // 출력 코드
    //Rectangle(g_hDC, 0, 0, 800, 600);
    Ellipse(g_hDC, g_tMonster.tSphere.x - g_tMonster.tSphere.radius,
        g_tMonster.tSphere.y - g_tMonster.tSphere.radius,
        g_tMonster.tSphere.x + g_tMonster.tSphere.radius,
        g_tMonster.tSphere.y + g_tMonster.tSphere.radius);
    Rectangle(g_hDC, g_tPlayerRC.left, g_tPlayerRC.top, g_tPlayerRC.right, g_tPlayerRC.bottom);
    

    for (auto iter = g_PlayerBulletList.begin(); iter != g_PlayerBulletList.end(); iter++)
    {
        Ellipse(g_hDC, (*iter).tSphere.x - (*iter).tSphere.radius,
            (*iter).tSphere.y - (*iter).tSphere.radius,
            (*iter).tSphere.x + (*iter).tSphere.radius,
            (*iter).tSphere.y + (*iter).tSphere.radius);
    }
    for (auto iter = g_MonsterBulletList.begin(); iter != g_MonsterBulletList.end(); iter++)
    {
        Ellipse(g_hDC, (*iter).tSphere.x - (*iter).tSphere.radius,
            (*iter).tSphere.y - (*iter).tSphere.radius,
            (*iter).tSphere.x + (*iter).tSphere.radius,
            (*iter).tSphere.y + (*iter).tSphere.radius);
    }
}