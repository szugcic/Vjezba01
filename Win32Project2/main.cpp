#include <windows.h>
const int id_button1 = 1;
const int id_button2 = 2;

void OnCreate(HWND hw)
{
	CreateWindow("BUTTON", "ONE",  WS_CHILD | WS_VISIBLE, 
		100, 100, 100, 30,
		hw, (HMENU)id_button1, 0, 0); 
	CreateWindow("BUTTON", "TWO", WS_CHILD | WS_VISIBLE, 
		100, 200, 100, 30,
		hw, (HMENU)id_button2, 0, 0); 
}

void OnComand(HWND hw, int id)
{
	switch (id)
	{
		case id_button1:
			MessageBox(hw, "one", "Clicked", MB_OK);
			break;
		case id_button2:
			MessageBox(hw, "two", "Clicked", MB_OK);
			break;
	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_CREATE:
			OnCreate(hwnd);
			break;
		case WM_COMMAND:
			OnComand(hwnd, LOWORD(wParam));
		    break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}


int RegisterMyClass(HINSTANCE hInstance, char* className)
{
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof wc);

	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = className;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hCursor = LoadCursor(NULL, IDC_HELP);
	//wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wc.hbrBackground = CreateSolidBrush(RGB(203,34,54));

	return RegisterClass(&wc);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	char clsName[] = "NWPClass";

	if(!RegisterMyClass(hInstance, clsName))
		return 0;

	HWND hwnd = CreateWindow(clsName, "NWP 1",  WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL); 

	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0))
		DispatchMessage(&msg);

	return msg.wParam;
}