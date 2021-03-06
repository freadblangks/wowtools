#pragma once
#include "base.h"
#include "CTimer.h"
#include "CInputReader.h"
#include "IVideoDriver.h"

class CRenderSetting;
class CLightSetting;
class CFontManager;
class CMeshManager;
class CMaterialManager;
class CTextureManager;

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
	CMaterialManager* getMaterialManager() const { return MaterialManager; }
	CRenderSetting* getRenderSetting() const { return RenderSetting; }
	CLightSetting* getLightSetting() const { return LightSetting; }
	CTextureManager* getTextureManager() const { return TextureManager; }

private:
	IVideoDriver*	Driver;
	SWindowInfo		WindowInfo;
	CTimer		Timer;
	CInputReader		InputReader;
	IMessageHandler*		MessageHandler;

	//
	CRenderSetting*		RenderSetting;
	CLightSetting*		LightSetting;
	CFontManager*		FontManager;
	CMeshManager*		MeshManager;
	CMaterialManager*	MaterialManager;
	CTextureManager*	TextureManager;
};

extern Engine* g_Engine;
