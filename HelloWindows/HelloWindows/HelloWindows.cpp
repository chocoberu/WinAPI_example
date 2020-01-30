// HelloWindows.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "HelloWindows.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다. 16비트 유니코드)
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

struct _tagArea
{
    bool bStart;
    POINT ptStart;
    POINT ptEnd;
};

_tagArea g_tArea; // 마우스 사용을 위한 전역 변수 
// Win32의 main() 함수 (엔트리 포인트 함수)
// H로 시작하는 경우 주로 handle을 의미, 
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, // 핸들 인스턴스, Windows OS가 프로그램을 구분하는 값
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow) // 윈도우를 보여주는 방식을 설정 (예 SH_SHOW)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING); // IDS_APP_TITLE 은 응용 프로그램의 타이틀을 가리키는 ID값
    LoadStringW(hInstance, IDC_HELLOWINDOWS, szWindowClass, MAX_LOADSTRING); 
    MyRegisterClass(hInstance); // 레지스터에 클래스 등록

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HELLOWINDOWS)); // 윈도우 리소스에서 제공하는 단축키 관련
    // 게임에서는 사용하지 않음
    // 게임에서 키 처리는 메시지 처리로 하지 않는다 (성능 문제)

    MSG msg; // 윈도우 메시지 구조체

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg); // 메시지를 해석
            DispatchMessage(&msg); // 
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex; // WNDCLASSEXW 구조체

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW; // 수직, 수평으로 redraw 가능
    wcex.lpfnWndProc    = WndProc; // Windows의 메시지를 처리하는 함수(윈도우 프로시저)의 포인터 
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HELLOWINDOWS));// icon
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW); // 커서
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOWFRAME +1); // 배경화면 색상
    wcex.lpszMenuName = NULL; // MAKEINTRESOURCEW(IDC_HELLOWINDOWS); 메뉴 이름
    wcex.lpszClassName  = szWindowClass; // 레지스터에 등록할 클래스 이름
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL)); // small icon 

    return RegisterClassExW(&wcex); // wcex의 값으로 레지스터에 등록
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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, // 기본 윈도우 클래스 이름과 타이틀 이름
       WS_OVERLAPPEDWINDOW, // 윈도우 스타일 
      CW_USEDEFAULT, 0, // 윈도우의 좌상단 좌표
       CW_USEDEFAULT, 0, // 윈도우 크기
       nullptr, // hWndParent 값 (부모 윈도우의 핸들값)
       nullptr, // hMenu값
       hInstance, // 인스턴스 핸들 값
       nullptr); // lpParam 값

   if (!hWnd)
   {
      return FALSE;
   }

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
    case WM_LBUTTONDOWN: // 마우스 왼쪽 버튼이 눌렸을 때
    {
        // 마우스 위치는 lParam에 들어오게 된다. 16비트로 쪼개서 x,y값이 32비트 변수에 들어오게 된다
        // LOWORD,HIWORD 매크로를 이용해서 하위, 상위 16비트의 값을 얻어올 수 있다.
        if (!g_tArea.bStart)
        {
            g_tArea.bStart = true;
            g_tArea.ptStart.x = lParam & 0x0000ffff; // 비트 연산
            g_tArea.ptStart.y = HIWORD(lParam); // 매크로 사용, 또는 lParam >> 16;
            
            InvalidateRect(hWnd, NULL, TRUE); // 강제로 WM_PAINT 메시지를 호출해주는 함수
            // hWnd : 윈도우 핸들
            // 갱신할 영역
            // 현재 화면을 지우고 갱신할지
        }
        break;
    }
    case WM_MOUSEMOVE:
    {
        if (g_tArea.bStart)
        {
            g_tArea.ptEnd.x = LOWORD(lParam);
            g_tArea.ptEnd.y = lParam >> 16;
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
    }
    case WM_LBUTTONUP:
    {
        if (g_tArea.bStart)
        {
            g_tArea.bStart = false;
            g_tArea.ptEnd.x = LOWORD(lParam);
            g_tArea.ptEnd.y = lParam >> 16;
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
    }
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
    case WM_PAINT: // 윈도우에 무언가를 그릴때
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps); // device context의 핸들
            
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            TextOut(hdc, 100, 100, L"Hello Win32!", 12);
            Rectangle(hdc, 150, 150, 300, 300); // (150,150) 좌상단, (300,300) 우하단 직사각형 그리기
            MoveToEx(hdc, 100, 300, NULL); // 선의 시작점 지정
            LineTo(hdc, 300, 400);
            LineTo(hdc, 300, 350); // 이전 점을 시작점으로 선을 그린다

            MoveToEx(hdc, 400, 400, NULL);
            LineTo(hdc, 500, 400);

            Ellipse(hdc, 150, 150, 300, 300); // 좌상단, 우하단 좌표 안에 들어가는 원(타원)을 그림

            // wsprintf : 유니코드 문자열로 만드는 함수
            // lstrlen : 유니코드 문자열의 길이를 반환하는 함수
            TCHAR strMouse[64] = {};
            
            wsprintf(strMouse, TEXT("Start = X : %d, Y : %d"), g_tArea.ptStart.x, g_tArea.ptStart.y);
            TextOut(hdc, 600, 300, strMouse, lstrlen(strMouse));

            if (g_tArea.bStart)
            {
                Rectangle(hdc, g_tArea.ptStart.x, g_tArea.ptStart.y, g_tArea.ptEnd.x, g_tArea.ptEnd.y);
            }

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY: // 윈도우 종료시 
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam); // 윈도우의 기본 기능으로 메시지 처리
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
