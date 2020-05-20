#include "Core.h"
#include "Scene/Scenemanager.h"
#include "../Include/Core/Timer.h"
#include "Core/PathManager.h"
#include "Resources/ResourcesManager.h"
#include "Resources/Texture.h"
#include "Core/Camera.h"
#include "Core/Input.h"
#include "Collider/CollisionManager.h"

Core* Core::m_pInst = NULL;
bool Core::m_bLoop = true;

Core::Core()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc();

#ifdef _DEBUG
    //콘솔창 생성함수.
    AllocConsole();

#endif

}



Core::~Core()
{
    DESTROY_SINGLE(Scenemanager);
    DESTROY_SINGLE(CResourcesManager);
    DESTROY_SINGLE(CPathManager);
    DESTROY_SINGLE(CTimer);
    DESTROY_SINGLE(CCamera);
    DESTROY_SINGLE(CInput);
    DESTROY_SINGLE(CCollisionManager);


    ReleaseDC(m_hWnd,m_hDc);

#ifdef _DEBUG
    //콘솔창 생성함수.
    FreeConsole();

#endif
}

bool Core::Init(HINSTANCE hInst)
{
	m_hInst = hInst;

	MyRegisterClass();


    //해상도 설정
    m_tRS.iW = 1280;
    m_tRS.iH = 720; 

    Create();

    //화면 DC를 만들어준다.
    m_hDc = GetDC(m_hWnd);

    //타이머 초기화
    if (!GET_SINGLE(CTimer)->Init(m_hWnd))
        return false;

    //경로관리자 초기화
    if (!GET_SINGLE(CPathManager)->Init())
        return false;

    //리소스관리자 초기화
    if (!GET_SINGLE(CResourcesManager)->Init(hInst,m_hDc))
        return false;

    //장면관리자 초기화
    if (!GET_SINGLE(Scenemanager)->Init())
        return false;
        
    //카메라관리자 초기화
    if (!GET_SINGLE(CCamera)->Init(POSITION(0.f,0.f),m_tRS,RESOLUTION(1500,1200)))
        return false;

    //입력관리자 초기화
    if (!GET_SINGLE(CInput)->Init(m_hWnd))
        return false;

    //충돌관리자 초기화
    if (!GET_SINGLE(CCollisionManager)->Init())
        return false;

	return true;
}

int Core::Run()
{
    MSG msg;


    // 기본 메시지 루프입니다:
    while (m_bLoop) //원래 : GetMessage(&msg, nullptr, 0, 0), 내가 임의로 메시지루프를 조정한다. 
        //GetMessage 가 아닌 PeekMessage를 사용하는이유 : GetMessage는 사용자의 메시지가 없으면 작동하지않는다.
        //반면 , PeekMessage는 사용자 메시지가 없어도 움직인다. 
        // 게임에서 내가 움직이지 않는다고 다른유저나, 애니메이션까지 가만히 있지는 않기때문에 PeekMessage를 사용해서 
        // 내 입력이 없어도 게임이 진행되는 것처럼 보여주기 위해서 PeekMessage를 사용한다. 

    {
        // PeekMessage는 메시지큐에 메시지가 없어도 빠져나간다.
        // 메시지가 있을 경우, true , 없을경우, false를 리턴한다.
        // 메시지가 없을 경우는 window가 deadtime 이 된다 .

        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

        }

        else // 실제 게임로직
        { 
            Logic();
        }
    }

    return (int)msg.wParam;
}

ATOM Core::MyRegisterClass()
{

    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = Core::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = m_hInst;
    wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL; //MAKEINTRESOURCEW(IDC_MY2DGAME2);
    wcex.lpszClassName = L"AR13API";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    return RegisterClassExW(&wcex);
}

LRESULT Core::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
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
        m_bLoop = false;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

BOOL Core::Create()
{

    m_hWnd = CreateWindowW(L"AR13API", L"AR13API", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInst, nullptr);

    if (!m_hWnd)
    {
        return FALSE;
    }


    // 실제 윈도우의 타이틀바나 메뉴바를 포함한 윈도우 크기를 구해준다.
    RECT rc = { 0,0,m_tRS.iW,m_tRS.iH };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

    SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, rc.right - rc.left,
        rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER); // 내가원하는위치에 윈도우를 띄우고, 크기를 지정
  


    ShowWindow(m_hWnd, SW_SHOW);
    UpdateWindow(m_hWnd);




    return TRUE;
}

void Core::Logic()
{
    GET_SINGLE(CTimer)->Update();
    
    float fDeltaTime = GET_SINGLE(CTimer)->GetDeltaTime();

    Input(fDeltaTime);
    Update(fDeltaTime);
    LateUpdate(fDeltaTime);
    Collision(fDeltaTime);
    Render(fDeltaTime);

}


void Core::Input(float fDeltaTime)
{
    GET_SINGLE(CInput)->Update(fDeltaTime);
    
    GET_SINGLE(Scenemanager)->Input(fDeltaTime);
    GET_SINGLE(CCamera)->Input(fDeltaTime);
}


int Core::Update(float fDeltaTime)
{
    GET_SINGLE(Scenemanager)->Update(fDeltaTime);
    GET_SINGLE(CCamera)->Update(fDeltaTime);
    return 0; 
}


int Core::LateUpdate(float fDeltaTime)
{
    GET_SINGLE(Scenemanager)->LateUpdate(fDeltaTime);
    return 0;
}

void Core::Collision(float fDeltaTime)
{
    GET_SINGLE(Scenemanager)->Collision(fDeltaTime);

    GET_SINGLE(CCollisionManager)->Collision(fDeltaTime);

}

void Core::Render(float fDeltaTime)
{
    //더블 버퍼링
    CTexture* pBackBuffer = GET_SINGLE(CResourcesManager)->GetBackBuffer();

    Rectangle(pBackBuffer->GetDC(), 0, 0, 1280, 720);

    GET_SINGLE(Scenemanager)->Render(pBackBuffer->GetDC(),fDeltaTime);

    BitBlt(m_hDc, 0, 0, 1280, 720, pBackBuffer->GetDC(), 0, 0, SRCCOPY);

    SAFE_RELEASE(pBackBuffer);

} 
