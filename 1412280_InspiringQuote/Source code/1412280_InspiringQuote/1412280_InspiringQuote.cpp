// 1412280_InspiringQuote.cpp : Defines the entry point for the application.
//

#include "1412280_InspiringQuote.h"
#include "Quote.h"
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
Quote quote;
int i = 0;
int flag = 0;
int bkImage=1;
NOTIFYICONDATA Tray;
// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK Setting(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY1412280_INSPIRINGQUOTE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY1412280_INSPIRINGQUOTE));

    MSG msg;

    // Main message loop:
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1412280_INSPIRINGQUOTE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY1412280_INSPIRINGQUOTE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
HWND button;
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_CAPTION | WS_SYSMENU ,
	   250, 100, 850, 500, nullptr, nullptr, hInstance, nullptr);
   Tray.cbSize = sizeof(Tray);
   Tray.hIcon = (HICON)LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_SMALL));
   Tray.hWnd = hWnd;
   Tray.uCallbackMessage = WM_SYSICON;
   Tray.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
   Tray.uID = 1;
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   quote.ReadFile();
   quote.Random();
   quote.SetAppHandle(hWnd);
   quote.GDIP_Init();
   quote.SetbackgroundImage(bkImage);
   quote.GetTextQuote(i);
   quote.GetTextAuthor(i);
   i++;
   button = CreateWindowEx(NULL, L"BUTTON", L"HIDE", BS_FLAT | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 682, 400, 152, 41, hWnd, (HMENU)IDC_BUTTON, NULL, NULL);
   Shell_NotifyIcon(NIM_ADD, &Tray);
   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	SetTimer(hWnd, IDC_TIMER, 5000, TIMERPROC(NULL));
    switch (message)
    {
	case WM_TIMER:
		switch (wParam)
		{
		case IDC_TIMER:
			ShowWindow(hWnd, 1);
			quote.SetbackgroundImage(bkImage);
			quote.GetTextQuote(i);
			quote.GetTextAuthor(i);
			i++;
			if (i >= quote.GetNumPack())
				i = 0;

			break;
		default:
			break;
		}
		break; 
	case WM_SYSICON:
		if (lParam == WM_LBUTTONUP)
		{
			ShowWindow(hWnd, 1);
			quote.SetbackgroundImage(bkImage);
			quote.GetTextQuote(i);
			quote.GetTextAuthor(i);
			i++;
			if (i >= quote.GetNumPack())
				i = 0;
		}
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
			case IDC_BUTTON:
				ShowWindow(hWnd, 0);
				Shell_NotifyIcon(NIM_ADD, &Tray);
				break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
			case ID_FILE_SETBACKGROUND:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_SETTING), hWnd, Setting);
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
            // TODO: Add any drawing code that uses hdc here...
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

// Message handler for about box.
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


//set screen's size
INT_PTR CALLBACK Setting(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:

		if (LOWORD(wParam) == IDCANCEL || LOWORD(wParam) == ID_SET_OK&&flag == 0) {
			flag = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

		if (LOWORD(wParam) == IDC_RADIO1)
		{
			flag = 1;
		}
		if (LOWORD(wParam) == IDC_RADIO2)
		{
			flag = 2;
		}
		if (LOWORD(wParam) == IDC_RADIO3)
		{
			flag = 3;
		}
		if (LOWORD(wParam) == ID_SET_OK && flag == 1) {
			if (i == 0)
				i = 5;
			bkImage = 1;
			flag = 0;
			quote.SetbackgroundImage(bkImage);
			quote.GetTextQuote(i - 1);
			quote.GetTextAuthor(i - 1);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == ID_SET_OK && flag == 2) {
			if (i == 0)
				i = 5;
			bkImage = 2;
			flag = 0;
			quote.SetbackgroundImage(bkImage);
			quote.GetTextQuote(i-1);
			quote.GetTextAuthor(i-1);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == ID_SET_OK && flag == 3) {
			if (i == 0)
				i = 5;
			bkImage = 3;
			flag = 0;
			quote.SetbackgroundImage(bkImage);
			quote.GetTextQuote(i - 1);
			quote.GetTextAuthor(i - 1);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDCANCEL) {
			flag = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
	}
	return (INT_PTR)FALSE;
}

