#include "Engine.h"
#include "mywow.h"
#include "CFontManager.h"
#include "CMeshManager.h"

Engine* g_Engine = nullptr;

bool createEngine(const SWindowInfo& wndInfo, E_DRIVER_TYPE driverType, bool vsync, E_AA_MODE aaMode, driverInitFunc initFunc)
{
	g_Engine = new Engine(wndInfo);

	if (!g_Engine->init(driverType, vsync, aaMode, initFunc))
	{
		goto fail;
	}

	return true;

fail:
	ASSERT(false);
	return false;
}

void destroyEngine()
{
	delete g_Engine;
	g_Engine = nullptr;
}


Engine::Engine(const SWindowInfo& wndInfo)
{
	WindowInfo = wndInfo;

	Driver = nullptr;
	FontManager = nullptr;
	MeshManager = nullptr;
}

Engine::~Engine()
{
	delete MeshManager;
	delete FontManager;
	delete Driver;
}

bool Engine::init(E_DRIVER_TYPE driverType, bool vsync, E_AA_MODE aaMode, driverInitFunc initFunc)
{
	if (WindowInfo.width == 0 || WindowInfo.height == 0 || !initFunc)
	{
		goto fail;
	}

	g_FileSystem->writeLog(ELOG_GX, "Engine Init...");

	Driver = initFunc(WindowInfo, driverType, vsync, aaMode);
	if (!Driver)
	{
		goto fail;
	}

	g_FileSystem->writeLog(ELOG_GX, "Create FontManager...");
	FontManager = new CFontManager(0, 0, 0, 12);
	FontManager->createDefaultFonts();

	g_FileSystem->writeLog(ELOG_GX, "Create MeshManager...");
	MeshManager = new CMeshManager();

	return true;

fail:
	ASSERT(false);
	return false;
}

void Engine::onWindowResized(const dimension2d& size)
{
	if (Driver)
		Driver->setDisplayMode(size);

}
