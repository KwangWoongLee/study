#include "Core.h"

Core* Core::m_pInst = NULL;
bool Core::m_bLoop = true;

Core::Core()
{

}

Core::~Core()
{
}

bool Core::Init(HINSTANCE hInst)
{
	m_hInst = hInst;

	MyRegisterClass();


    //�ػ� ����
    m_tRS.iW = 1280;
    m_tRS.iH = 720; 

    Create();

	return true;
}

int Core::Run()
{
    MSG msg;


    // �⺻ �޽��� �����Դϴ�:
    while (m_bLoop) //���� : GetMessage(&msg, nullptr, 0, 0), ���� ���Ƿ� �޽��������� �����Ѵ�. 
        //GetMessage �� �ƴ� PeekMessage�� ����ϴ����� : GetMessage�� ������� �޽����� ������ �۵������ʴ´�.
        //�ݸ� , PeekMessage�� ����� �޽����� ��� �����δ�. 
        // ���ӿ��� ���� �������� �ʴ´ٰ� �ٸ�������, �ִϸ��̼Ǳ��� ������ ������ �ʱ⶧���� PeekMessage�� ����ؼ� 
        // �� �Է��� ��� ������ ����Ǵ� ��ó�� �����ֱ� ���ؼ� PeekMessage�� ����Ѵ�. 

    {
        // PeekMessage�� �޽���ť�� �޽����� ��� ����������.
        // �޽����� ���� ���, true , �������, false�� �����Ѵ�.
        // �޽����� ���� ���� window�� deadtime �� �ȴ� .

        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

        }

        else
        { 

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
        // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
        EndPaint(hWnd, &ps);
    }
    break;
    //�����츦 ������ �� ������ �޽���.
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


    // ���� �������� Ÿ��Ʋ�ٳ� �޴��ٸ� ������ ������ ũ�⸦ �����ش�.
    RECT rc = { 0,0,800,600 };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

    SetWindowPos(m_hWnd, HWND_TOPMOST, 100, 100, rc.right - rc.left,
        rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER); // �������ϴ���ġ�� �����츦 ����, ũ�⸦ ����

    ShowWindow(m_hWnd, SW_SHOW);
    UpdateWindow(m_hWnd);




    return TRUE;
}