#include "base.h"
#include "mywow.h"
#include <crtdbg.h>

#include "game.h"

#pragma comment(lib, "mywow.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")

int main()
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	
	SWindowInfo wndInfo = CSysUtil::createWindow("app1", 1136, 640, false, false);
	HWND hwnd = wndInfo.hwnd;

	SRendererInfo rendererInfo;
	rendererInfo.adapter = 0;
	rendererInfo.vsync = true;
	rendererInfo.antialias = 1;

	if (!createEngine(wndInfo, rendererInfo))
	{
		destroyEngine();
		return -1;
	}

	MyMessageHandler handler;
	g_Engine->setMessageHandler(&handler);

	createInput();

	MSG msg;
	while (!g_bExit)
	{
		if (::PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		else
		{
			bool active = !g_bBackMode && ::GetActiveWindow() == hwnd;
			if (active)
			{
				processInput();
			}

			::Sleep(1);
		}
	}

	destroyInput();

	destroyEngine();

	return 0;
}