#include <windows.h>
#include "scenemanager.h"

#define WIN32_LEAN_AND_MEAN

SceneManager* g_pscene = 0;

LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_QUIT:
	case WM_DESTROY:
	case WM_CLOSE:
		PostQuitMessage(0);
		DestroyWindow(hwnd);
		break;
	default:
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//setup window class props
	WNDCLASSEX wc;
	HWND hwnd;
	MSG msg;

	g_pscene = new SceneManager;

	wc.cbClsExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = L"graphc_core_class";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if(!RegisterClassEx(&wc))
	{
		g_pscene->Close();
		delete g_pscene;
		g_pscene = 0;
		return 0;
	}

	//setup the window
	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
						  L"graphc_core_class",
						  L"GraphcisCoreTestApp",
						  WS_OVERLAPPEDWINDOW,
						  CW_USEDEFAULT,
						  CW_USEDEFAULT,
						  1200,
						  840,
						  NULL,
						  NULL,
						  hInstance,
						  NULL);

	if(hwnd == NULL)
	{
		g_pscene->Close();
		delete g_pscene;
		g_pscene = 0;
		return 0;
	}

	//after check init the scene
	if(!g_pscene->InitScene(hwnd, 1200, 840))
	{
		MessageBox(NULL, L"Scene start failed", L"Graphic Error", MB_OK);
		g_pscene->Close();
		delete g_pscene;
		g_pscene = 0;
		return 0;
	}

	//setup some mem
	ZeroMemory(&msg, sizeof(msg));

	while(msg.message != WM_QUIT)
	{
		ShowWindow(hwnd, SW_SHOW);
		UpdateWindow(hwnd);

		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
			g_pscene->Render();
	}
	
	g_pscene->Close();
	delete g_pscene;
	g_pscene = 0;
	UnregisterClass(L"graphc_core_class", hInstance);

	return 0;						
}