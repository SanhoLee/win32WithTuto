#include <Windows.h>

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void AddMenus(HWND);

HMENU hMenu;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int nCmdShow) {
	
	// 윈도우 클래스 선언.
	WNDCLASSW wc = { 0 };

	// 클래스의 속성정의
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInst;
	//className으로 클래스를 구별한다?
	wc.lpszClassName = L"myWindowClass";
	wc.lpfnWndProc = WndProc;


	// 클래스 등록
	if(!RegisterClassW(&wc))
		return -1;
	
	 /*
	 1.Window Class name
	 2.Window Headline name
	 3.WS: Window Style
	 4.

	 */
	CreateWindowW(
		L"myWindowClass", 
		L"My Window Headline",
		WS_OVERLAPPED | WS_VISIBLE, 
		100,100,500,500,
		NULL,NULL,NULL,NULL);

	// message loop
	MSG msg = { 0 };
	while (GetMessage(&msg,NULL,NULL,NULL) ){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;

}


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) 
{
	switch (msg)
	{
	case WM_COMMAND:
		//WPARAM 을 통해서 커맨드 메세지가 들어온다.
		switch (wp)
		{
		case FILE_MENU_EXIT:
			DestroyWindow(hWnd);
			break;
		case FILE_MENU_NEW:
			MessageBeep(MB_ICONINFORMATION);
			break;
		}


		break;

	case WM_CREATE:
		AddMenus(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		// 모든 메세지 처리후 디폴트일 경우 처리하는 로직.
		return DefWindowProcW(hWnd, msg, wp, lp);
	}

}

void AddMenus(HWND hWnd) 
{
	hMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();
	HMENU hSubMenu = CreateMenu();

	AppendMenu(hSubMenu, MF_STRING, NULL, L"SubMenu Item 1");

	
	// submenu for "FILE" menu.
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, L"New");
	AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR)hSubMenu, L"Open SubMenu");
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, L"Exit");



	// append items on menu.
	// string type : MF_STRING
	// SUB MENU : MF_POPUP
	//AppendMenu(hMenu, MF_STRING, 1, L"FILE");
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"FILE");
	AppendMenu(hMenu, MF_STRING, NULL, L"HELP");




	SetMenu(hWnd, hMenu);

}
