// 2dGame_2.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "2dGame_2.h"
#include <list>
#include <math.h>

using namespace std;

typedef struct _tacSphere {
    float x;
    float y;
    float r;

}SPHERE, *PSPHERE;

typedef struct _tagRectangle {
    float left, right, top, bottom;

} RECTANGLE, *PRECTANGLE;

typedef struct _tagBullet {
    SPHERE tSphere;
    float fDist;
    float fLimitDist;
    float fAngle;
} BULLET, *PBULLET;

typedef struct _tagMonster {
    SPHERE tSphere;
    float fSpeed;
    float fTime;
    float fLimitTime;
    int iDir;
}MONSTER, *PMONSTER;
#define MAX_LOADSTRING 100
#define PI 3.14159f

void Run();
// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND    g_hWnd;
HDC     g_hdc;
bool    g_bLoop = true;
SPHERE    g_tPlayer = { 50.f,50.f, 50.f};
POINT g_tGunPos;
float g_fPlayerAngle;
float g_fGunLength = 70.f;
MONSTER g_tMonster;


//플레이어 총알 구현을 위한 리스트
list<BULLET> g_PlayerBulletList;

//몬스터 총알
list<BULLET> g_MonsterBulletList;


//시간을 구하기 위한 변수들
LARGE_INTEGER g_tSecond;
LARGE_INTEGER g_tTime;
float g_fDeltaTime;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_MY2DGAME2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    //화면용 DC생성
    g_hdc = GetDC(g_hWnd);

    //몬스터 초기화
    g_tMonster.tSphere.x = 800.f - 50.f;
    g_tMonster.tSphere.y = 300.f;
    g_tMonster.tSphere.r = 50.f;
    g_tMonster.fSpeed = 300.f;
    g_tMonster.iDir = 1;
    g_tMonster.fLimitTime = 2.f;
    g_tMonster.fTime = 0.f;

    //플레이어 총구의 위치
    g_tGunPos.x = g_tPlayer.x + cosf(g_fPlayerAngle) * g_fGunLength;
    g_tGunPos.y = g_tPlayer.y + sinf(g_fPlayerAngle) * g_fGunLength;



    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY2DGAME2));

    MSG msg;

    QueryPerformanceFrequency(&g_tSecond);
    QueryPerformanceCounter(&g_tTime);

    // 기본 메시지 루프입니다:
    while (g_bLoop) //원래 : GetMessage(&msg, nullptr, 0, 0), 내가 임의로 메시지루프를 조정한다. 
        //GetMessage 가 아닌 PeekMessage를 사용하는이유 : GetMessage는 사용자의 메시지가 없으면 작동하지않는다.
        //반면 , PeekMessage는 사용자 메시지가 없어도 움직인다. 
        // 게임에서 내가 움직이지 않는다고 다른유저나, 애니메이션까지 가만히 있지는 않기때문에 PeekMessage를 사용해서 
        // 내 입력이 없어도 게임이 진행되는 것처럼 보여주기 위해서 PeekMessage를 사용한다. 

    {
        // PeekMessage는 메시지큐에 메시지가 없어도 빠져나간다.
        // 메시지가 있을 경우, true , 없을경우, false를 리턴한다.
        // 메시지가 없을 경우는 window가 deadtime 이 된다 .

        if (PeekMessage(&msg,nullptr,0,0, PM_REMOVE)) 
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

        }

        else 
        { //윈도우가 deadtime인 경우 : 게임을 개발하는 부분
            Run(); //내가 임의로 만든 함수 Run()을 사용하여 PeekMessage가 없을 경우 Run()이 실행되도록 한다.

        }
    }

    ReleaseDC(g_hWnd, g_hdc);

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY2DGAME2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName = NULL; //MAKEINTRESOURCEW(IDC_MY2DGAME2);
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
   g_hWnd = hWnd;
   // 실제 윈도우의 타이틀바나 메뉴바를 포함한 윈도우 크기를 구해준다.
   RECT rc = { 0,0,800,600 };
   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

   SetWindowPos(hWnd, HWND_TOPMOST, 100, 100, rc.right - rc.left,
       rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER); // 내가원하는위치에 윈도우를 띄우고, 크기를 지정

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
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
        //윈도우를 종료할 때 들어오는 메시지.
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

void Run(){
    //DeltaTime 을 구해준다.
    LARGE_INTEGER tTime;
    QueryPerformanceCounter(&tTime);

    g_fDeltaTime = (tTime.QuadPart - g_tTime.QuadPart) / (float)g_tSecond.QuadPart;

    g_tTime = tTime;

    static float fTimeScale = 1.f;
    if (GetAsyncKeyState(VK_F1) & 0x8000) {
        fTimeScale -= g_fDeltaTime;
        if (fTimeScale < 0.f)
            fTimeScale = 0.f;
    }
    if (GetAsyncKeyState(VK_F2) & 0x8000) {
        fTimeScale += g_fDeltaTime;
        if (fTimeScale > 1.f)
            fTimeScale = 1.f;
    }

    //플레이어 초당 이동속도 :300
    float fSpeed = (400.f) * g_fDeltaTime * fTimeScale;


    if (GetAsyncKeyState('D') & 0x8000)
    {
        g_fPlayerAngle += PI * g_fDeltaTime * fTimeScale;
    }
    if (GetAsyncKeyState('A') & 0x8000)
    {
        g_fPlayerAngle -= PI * g_fDeltaTime * fTimeScale;
    }
    if (GetAsyncKeyState('W') & 0x8000)
    {
        g_tPlayer.x += fSpeed * cosf(g_fPlayerAngle) * fTimeScale;
        g_tPlayer.y += fSpeed * sinf(g_fPlayerAngle) * fTimeScale;

    }
    if (GetAsyncKeyState('S') & 0x8000)
    {
        g_tPlayer.x -= fSpeed * cosf(g_fPlayerAngle) * fTimeScale;
        g_tPlayer.y -= fSpeed * sinf(g_fPlayerAngle) * fTimeScale;

    }
    //총구위치를 구한다.
    g_tGunPos.x = g_tPlayer.x + cosf(g_fPlayerAngle) * g_fGunLength;
    g_tGunPos.y = g_tPlayer.y + sinf(g_fPlayerAngle) * g_fGunLength;

    if (GetAsyncKeyState(VK_SPACE) & 0x8000)
    {
        BULLET tBullet;

        tBullet.tSphere.x = g_tGunPos.x ;
        tBullet.tSphere.y = g_tGunPos.y ;
        tBullet.tSphere.r = 25.f;

        tBullet.fDist = 0.f;
        tBullet.fLimitDist = 500.f;
        tBullet.fAngle = g_fPlayerAngle;
        g_PlayerBulletList.push_back(tBullet);
    }

    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
    {
        //마우스 위치 얻어오기.
        POINT ptMouse;
        GetCursorPos(&ptMouse); // 여기서 얻은 포인트는 스크린좌표
        // 아래 함수를 통해 클라이언트 좌표로 변환
        ScreenToClient(g_hWnd, &ptMouse);


        float fMX = g_tMonster.tSphere.x - ptMouse.x;
        float fMY = g_tMonster.tSphere.y - ptMouse.y;
        float fMDist = sqrtf(fMX * fMX + fMY * fMY);

        //플레이어와 충돌처리

        if (fMDist <= g_tMonster.tSphere.r)
        {
            MessageBox(NULL, L"몬스터 클릭", L"마우스클릭", MB_OK);
        }

        fMX = g_tPlayer.x - ptMouse.x;
        fMY = g_tPlayer.y - ptMouse.y;
        fMDist = sqrtf(fMX * fMX + fMY * fMY);

        if (fMDist <= g_tPlayer.r)
        {
            MessageBox(NULL, L"플레이어클릭", L"마우스클릭", MB_OK);
        }
    }

    RECT rcWindow;
    GetClientRect(g_hWnd, &rcWindow);
    SetRect(&rcWindow, 0, 0, 800, 600);

    if (g_tPlayer.x < rcWindow.left +g_tPlayer.r)
    {
        g_tPlayer.x = rcWindow.left + g_tPlayer.r;
    }
    else if (g_tPlayer.x > rcWindow.right - g_tPlayer.r)
    {
        g_tPlayer.x = rcWindow.right - g_tPlayer.r;
    }
    if (g_tPlayer.y < rcWindow.top + g_tPlayer.r)
    {
        g_tPlayer.y = rcWindow.top + g_tPlayer.r;
    }
    else if (g_tPlayer.y > rcWindow.bottom - g_tPlayer.r)
    {
        g_tPlayer.y = rcWindow.bottom - g_tPlayer.r;
    }

    list<BULLET>::iterator iter;
    list<BULLET>::iterator iterEnd = g_PlayerBulletList.end();

    

    //몬스터 이동
    g_tMonster.tSphere.y += g_tMonster.fSpeed * g_fDeltaTime * fTimeScale * g_tMonster.iDir;

    if (g_tMonster.tSphere.y+ g_tMonster.tSphere.r >= 600.f)
    {
        g_tMonster.iDir *= -1;
        g_tMonster.tSphere.y = 550.f;

    }
    else if (g_tMonster.tSphere.y - g_tMonster.tSphere.r <= 0.f)
    {
        g_tMonster.iDir *= -1;
        g_tMonster.tSphere.y = 50.f;
        
    }

    g_tMonster.fTime += g_fDeltaTime;
    if (g_tMonster.fTime >= g_tMonster.fLimitTime) 
    {
        g_tMonster.fTime -= g_tMonster.fLimitTime;

        BULLET tBullet = {};

        tBullet.tSphere.x = g_tMonster.tSphere.x - g_tMonster.tSphere.r/2.f;
        tBullet.tSphere.y = g_tMonster.tSphere.y;
        tBullet.tSphere.r = g_tMonster.tSphere.r / 2.f;
        tBullet.fDist = 0.f;
        tBullet.fLimitDist = 800.f;
        tBullet.fAngle = -g_fPlayerAngle;
       
        g_MonsterBulletList.push_back(tBullet);

    }


    //플레이어 총알 이동
    fSpeed = (300.f) * g_fDeltaTime * fTimeScale;
    iterEnd = g_PlayerBulletList.end();
    for (iter = g_PlayerBulletList.begin(); iter != iterEnd;)
    {
        (*iter).tSphere.x += cosf((*iter).fAngle)*fSpeed;
        (*iter).tSphere.y += sinf((*iter).fAngle)*fSpeed;
        (*iter).fDist += fSpeed;

        float fX = (*iter).tSphere.x - g_tMonster.tSphere.x;
        float fY = (*iter).tSphere.y - g_tMonster.tSphere.y;
        float fDist = sqrtf(fX * fX + fY * fY);

        if (fDist <= (*iter).tSphere.r + g_tMonster.tSphere.r)
        {
            iter = g_PlayerBulletList.erase(iter);
            iterEnd = g_PlayerBulletList.end();
        }


        else if ((*iter).fDist >= (*iter).fLimitDist)
        {
            iter = g_PlayerBulletList.erase(iter);
            iterEnd = g_PlayerBulletList.end();

        }

        else if ((*iter).tSphere.x + (*iter).tSphere.r >= 800)
        {
            iter = g_PlayerBulletList.erase(iter);
            iterEnd = g_PlayerBulletList.end();
        }
        else
        {
            ++iter;
        }

    }

    //몬스터 총알 이동
    iterEnd = g_MonsterBulletList.end();
    for (iter = g_MonsterBulletList.begin(); iter != iterEnd;)
    {
        (*iter).tSphere.x -= fSpeed;
        (*iter).fDist += fSpeed;

        float fX = (*iter).tSphere.x - g_tPlayer.x;
        float fY = (*iter).tSphere.y - g_tPlayer.y;
        float fDist = sqrtf(fX * fX + fY * fY);



        // if 문 걸어서 플레이어와 몬스터의 총알 충돌처리 하기


        //

        if ((*iter).fDist >= (*iter).fLimitDist)
        {
            iter = g_MonsterBulletList.erase(iter);
            iterEnd = g_MonsterBulletList.end();

        }

        else if ((*iter).tSphere.x - (*iter).tSphere.r <= 0)
        {
            iter = g_MonsterBulletList.erase(iter);
            iterEnd = g_MonsterBulletList.end();
        }

        else
        {
            ++iter;
        }

    }

    Rectangle(g_hdc, 0, 0, 800, 600);
    //내 hdc를 만듦으로써 paind 메세지로 가지 않고도 그림을 그렸다.
    Ellipse(g_hdc, g_tPlayer.x - g_tPlayer.r, g_tPlayer.y + g_tPlayer.r,
        g_tPlayer.x + g_tPlayer.r, g_tPlayer.y - g_tPlayer.r);
    MoveToEx(g_hdc, g_tPlayer.x, g_tPlayer.y, NULL);
    LineTo(g_hdc, g_tGunPos.x, g_tGunPos.y);

    //몬스터 그려주기
    
    Ellipse(g_hdc, g_tMonster.tSphere.x - g_tMonster.tSphere.r, g_tMonster.tSphere.y + g_tMonster.tSphere.r,
        g_tMonster.tSphere.x + g_tMonster.tSphere.r, g_tMonster.tSphere.y - g_tMonster.tSphere.r);
    iterEnd = g_PlayerBulletList.end();
    for (iter = g_PlayerBulletList.begin(); iter != iterEnd; iter++)
    {

        Ellipse(g_hdc, (*iter).tSphere.x - (*iter).tSphere.r, (*iter).tSphere.y + (*iter).tSphere.r, (*iter).tSphere.x + (*iter).tSphere.r, (*iter).tSphere.y - (*iter).tSphere.r);

    }
    iterEnd = g_MonsterBulletList.end();
    for (iter = g_MonsterBulletList.begin(); iter != iterEnd; iter++)
    {

        Ellipse(g_hdc, (*iter).tSphere.x - (*iter).tSphere.r, (*iter).tSphere.y + (*iter).tSphere.r, (*iter).tSphere.x + (*iter).tSphere.r, (*iter).tSphere.y - (*iter).tSphere.r);

    }
    


}
