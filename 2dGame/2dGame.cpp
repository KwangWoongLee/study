// 2dGame.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "2dGame.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
static POINT ptStart = { 0,0 };
static POINT ptEnd = { 0,0 };
static POINT ptMouse = { 0,0 };
BOOLEAN click = FALSE;

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
    LoadStringW(hInstance, IDC_MY2DGAME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY2DGAME));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
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
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY2DGAME));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName = NULL;// MAKEINTRESOURCEW(IDC_MY2DGAME); 메뉴제거
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

    case WM_LBUTTONDOWN: // 마우스 왼쪽버튼 눌렀을 때 메시지
        {
            //이 메시지가 들어올 경우 lParam을 통해 32비트의 값을 받는데 상위 16비트는 x 하위 16비트는 y값을 나타낸다.
            //LOWORD 와 HIWORD 매크로를 통해 각 x,y값을 얻는다. 

        if (!click) 
        {
            click = TRUE;
            ptStart.x = lParam & 0x0000ffff;
            ptStart.y = lParam >> 16;
            ptEnd.x = ptStart.x;
        }
        
            // 강제로 WM_PAINT 메시지를 호출하는 함수
            // 1번인자는 윈도우 핸들러
            // 2번인자는 초기화 영역 , NULL일 경우 , 전체화면 갱신
            // 3번인자는 true일경우 화면을 지우고 갱신 ,false 일 경우 현재화면을 안지우고 갱신
            InvalidateRect(hWnd, NULL, TRUE);
        

        

        break;
        }
        //마우스가 움직일 때 들어오는 메시지
    case WM_MOUSEMOVE:
        {
        if (click)
        {
            ptEnd.x = lParam & 0x0000ffff;
            ptEnd.y = lParam >> 16;
            InvalidateRect(hWnd, NULL, TRUE);
        }

        break;
        }
        //마우스 왼쪽 버튼을 떼었을 때 발생하는 메시지
    case WM_LBUTTONUP:
        {
        
        if (click)
        {
            click = FALSE;
            ptEnd.x = lParam & 0x0000ffff;
            ptEnd.y = lParam >> 16;
            InvalidateRect(hWnd, NULL, TRUE);

        }

        break;
        }


    case WM_KEYDOWN: // 키가 눌러졌을 때 메시지 
        {
            //이 메세지가 들어올 경우 wParam이라는 변수를 통해 어떤키가 눌렸는지가 전달됨.
            switch (wParam)
            {
                case VK_ESCAPE://esc키
                    DestroyWindow(hWnd); //윈도우 창 핸들러 
                    break;
                default:
                    break;
            }
        break;
        }

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps); //클라이언트 화면 dc

                //문자출력함수 
            //L""은 유니코드 문자열을 위해 문자열 앞에 L을 붙여주는 것이다.
            // 아니면 TEXT매크로를 사용하는 방법도 있다. TEXT()
            TextOut(hdc, 50, 50, L"하이",2); // 문자열 출력함수 인자1 : 텍스트를 띄울 핸들 , 인자2,3 : 좌표  , 인자4 : 출력을 원하는 문자열, 인자5 : 인자4의 길이


            TCHAR strMouse[64] = {};
            //유니코드 문자열을 만들어 대입하는 함수;
            wsprintf(strMouse, TEXT("x : %d, y : %d"),ptStart.x, ptStart.y);
            //lstrlen은 유티코드 문자열의 길이를 구하는 함수
            TextOut(hdc, 600, 30, strMouse, lstrlen(strMouse));


            // 드래그 사각형 그리기
            if (click)
            {
                MoveToEx(hdc, ptStart.x, ptStart.y, NULL);
                Rectangle(hdc, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);

            }

                //도형출력함수 
            //사각형
            Rectangle(hdc, 100, 100, 200, 200); //뜻 : hdc에 왼쪽 끝점좌표(100,100) 오른쪽 끝점좌표(200,200)인 사각형을 그려줘
            //선
            MoveToEx(hdc,300,100,NULL);//선의 시작점 정의 , lppt(4번째인자) 는 null을 줘도됨 
            LineTo(hdc, 400, 150); // 선의 끝점 정의
            MoveToEx(hdc, 500, 100, NULL);
            LineTo(hdc, 500, 200); // 두번째 LineTo를 호출했을 때는 , 이전의 끝점에서 시작되므로, 다시 MoveToEx를 호출해서 시작점을 설정해줘야함 .

            Ellipse(hdc, 100, 100, 200, 200); //끝점(100,100)과 끝점(200,200)으로 그려지는 사각형에 꽉차게 그려지는 원 





            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
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
