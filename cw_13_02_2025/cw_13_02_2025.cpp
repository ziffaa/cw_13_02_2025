#include <windows.h>
#include <tchar.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{

	// создаём главное окно приложения на основе модального диалога
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

BOOL isHolding = FALSE;
INT startX, startY;
INT endX, endY;
INT count = 0;
static HWND hStatic;

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_SHOWWINDOW:
		//MessageBox(0, TEXT("Test"), 0, MB_OK);
		return TRUE;
	case WM_CLOSE:
		EndDialog(hWnd, 0); // закрываем модальный диалог
		return TRUE;
	case WM_MOUSEMOVE:
		if (isHolding)
		{
			endX = LOWORD(lParam);
			endY = HIWORD(lParam);
		}
		else
		{
			startX = LOWORD(lParam);
			startY = HIWORD(lParam);
		}
		return TRUE;
	case WM_LBUTTONDOWN:
		isHolding = TRUE;
		return TRUE;
	case WM_LBUTTONUP:
		RECT rect;
		GetWindowRect(hWnd, &rect);
		isHolding = FALSE;
		int left = min(startX, endX);
		int top = min(startY, endY);
		int width = abs(endX - startX);
		int height = abs(endY - startY);

		if (width > 10 && height > 10)
		{
			hStatic = CreateWindowEx(0, TEXT("STATIC"), 0,
				WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | WS_EX_CLIENTEDGE,
				left, top, width, height, hWnd, 0, nullptr, 0);
			count++;
			TCHAR str[50];
			_stprintf_s(str, 50, _T("%d"), count);
			SetWindowText(hStatic, str);
		}
		else
		{
			MessageBox(NULL, TEXT("Area of selection is too small!"), TEXT("Warning"), MB_OK | MB_ICONWARNING);
		}
		return TRUE;
	}
	return FALSE;
}