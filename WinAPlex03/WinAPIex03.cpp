#include <windows.h>
#include "resource.h"
#include <iostream>

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstanc, LPSTR lpCmdLine, int nShowCmd)

{
	char szTitle[] = "My First Window Program";
	char szClass[] = "Class";

	// 1. Declare window class -----------------------------------------------------

	WNDCLASSEX WndEx;
	WndEx.style = NULL; // window style
	WndEx.lpfnWndProc = WndProc; //window procedure(function) pointer
	WndEx.cbClsExtra = 0; //additional memory size for widow class
	WndEx.cbWndExtra = 0; // additional memory size for window
	WndEx.hInstance = hInstance; // intance handle of the window procdeure
	WndEx.hIcon = LoadIcon(NULL, ""); //big icon
	WndEx.hIconSm = LoadIcon(hInstance, ""); //small icon
	WndEx.hCursor = LoadCursor(NULL, IDC_ARROW);//cursor
	WndEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//background
	WndEx.lpszMenuName = "IDR_MENU";//menui
	WndEx.lpszClassName = szClass;//window class name
	WndEx.cbSize = sizeof(WndEx); //size of window class structure

	// 2. Register window calss -----------------------------------------------------

	RegisterClassEx(&WndEx);

	// 3. Create window -------------------------------------------------------------
	HWND hWnd;
	hWnd = CreateWindowEx(NULL, szClass, szTitle,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		320 * 2, 240 * 2, NULL, NULL, hInstance, NULL);

	// 4. Show and Update window-----------------------------------------------------

	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);

	// 5. Message loop --------------------------------------------------------------

	MSG mSg;
	while (TRUE)
	{
		if (PeekMessage(&mSg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage(&mSg, NULL, 0, 0))
				break;
			TranslateMessage(&mSg);
			DispatchMessage(&mSg);
		}
	}
	return mSg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC = GetDC(hWnd);
	char szText1[] = "Left mouse button down";
	char szText2[] = "Left mouse button up";
	char szText3[] = "Right mouse button down";
	char szText4[] = "Right mouse button up";
	char szNewTitle[] = "This is a new title example";
	char szTextT[100];

	//static char a = 0;
	static int keyflag = 0;
	//static int a, b;
	static int a = 0, b = 0;

	PAINTSTRUCT pS;


	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (LOWORD(wParam) == VK_RETURN) /* Enter key */ {
			SetTimer(hWnd, 1, 1000, NULL); /* Make timer*/
		}

		else if (LOWORD(wParam) == VK_SPACE) {
			KillTimer(hWnd, 1); /* Kill Timer*/
		}
			return FALSE;

	case WM_TIMER:
		a++;
		if (a == 60) {
			b++;
			a = 0;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);
		sprintf_s(szTextT, "Minute: %d,   Second: %d ", b, a);
			TextOut(hDC, 5, 50, szTextT, lstrlen(szTextT));

		return FALSE;

	case WM_DESTROY:
		PostQuitMessage(0);
		return FALSE;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
