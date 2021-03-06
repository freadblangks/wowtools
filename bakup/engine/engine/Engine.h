#pragma once
#include "base.h"
#include "CTimer.h"
#include "CInputReader.h"
#include "IVideoDriver.h"
#include "CRenderSetting.h"

class CFontManager;
class CMeshManager;

using driverInitFunc = std::function<IVideoDriver*(const SWindowInfo& wndInfo,
	E_DRIVER_TYPE driverType, bool vsync, E_AA_MODE aaMode)>;

//
bool createEngine(const SWindowInfo& wndInfo, E_DRIVER_TYPE driverType, bool vsync, E_AA_MODE aaMode, driverInitFunc initFunc);
void destroyEngine();

class Engine
{
public:
	explicit Engine(const SWindowInfo& wndInfo);
	~Engine();

public:
	bool init(E_DRIVER_TYPE driverType, bool vsync, E_AA_MODE aaMode, driverInitFunc initFunc);

	void setMessageHandler(IMessageHandler* messageHandler) { MessageHandler = messageHandler; }
	IMessageHandler* getMessageHandler() { return MessageHandler; }

	void onWindowResized(const dimension2d& size);

public:
	IVideoDriver* getDriver() const { return Driver; }
	const SWindowInfo& getWindowInfo() const { return WindowInfo; }
	CInputReader* getInputReader() { return &InputReader; }
	CFontManager* getFontManager() const { return FontManager; }
	CMeshManager* getMeshManager() const { return MeshManager; }
	const CRenderSetting& getRenderSetting() const { return RenderSetting; }

private:
	IVideoDriver*	Driver;
	SWindowInfo		WindowInfo;
	CTimer		Timer;
	CInputReader		InputReader;
	IMessageHandler*		MessageHandler;

	//
	CRenderSetting		RenderSetting;
	CFontManager*		FontManager;
	CMeshManager*		MeshManager;
};

extern Engine* g_Engine;
