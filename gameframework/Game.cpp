#include "Game.h"
#include <lilib/Misc.h>
#include <glrenderer/Wrapper.h>
#include <audio/AudioEngine.h>
#include <glrenderer/MiscFunctions.h>
#include <platform/win32/Win32Header.h>
#include <platform/InputCodes.h>
#include <glrenderer/ScreenQuad.h>
#include <glrenderer/Sprite.h>
#include <glrenderer/Skybox.h>
#include <glrenderer/FontGraphics.h>
#include <glrenderer/GUIGraphics.h>
#include <gameframework/Debug.h>
#include <gameframework/CrashLog.h>
#include "Profiler.h"

void liGame::BaseLoadContent()
{
	//content->LoadContent();
}

liGame::liGame()
{
	LiMemory_Init();
}

liGame::~liGame()
{
}

void liGame::Startup(liString title, int width, int height)
{
	LiLib_SetSeed(time(NULL));
	Sys_Setup(title.c_str(), 1280, 720);
	Sys_StartWindow();
	Sys_SetupConsole();
	Sys_StartupGL();
	WrapperGL_LoadFunctions();
	MiscRendererFunctions::SetVsync(true);
	AudioEngine_Startup();
	liProfiler::Startup();
	ScreenQuad::Instance = new ScreenQuad();
	Sprite::InitializeSpriteGraphics();
	Skybox::InitializeSkyboxGraphics();
	FontGraphics::Initialize();
	GUIGraphics::Initialize();
	MiscRendererFunctions::SetViewport(GetWidth(), GetHeight());
	if(!Sys_FolderExists("logs"))
		Sys_CreateFolder("logs");
	this->crash_logs = new liFileSystem("logs");
	if (!Sys_FolderExists("configs"))
		Sys_CreateFolder("configs");
	this->config_files = new liFileSystem("configs");
	CrashLog::SetupCrashLogs(crash_logs);
	this->fs = new liFileSystem("assets");
	this->content = new liContentManager(fs);
	this->closed = false;
}

void liGame::Shutdown()
{
	delete ScreenQuad::Instance;
	delete content;
	delete config_files;
	delete crash_logs;
	delete fs;
	GUIGraphics::Shutdown();
	FontGraphics::Shutdown();
	Skybox::ShutdownSkyboxGraphics();
	Sprite::ShutdownSpriteGraphics();
	liProfiler::Shutdown();
	AudioEngine_Shutdown();
	Sys_ShutdownGL();
	Sys_CloseWindow();
	if (liMemory::Instance->GetUsage() > 0) {
		Debug::LogWarning(liString("Possible memory leak: ") + liString::IntToString(liMemory::Instance->GetUsage()) + liString(" stray bytes!"));
	}
	LiMemory_Shutdown();
}

void liGame::Run()
{
	MiscRendererFunctions::EnableDepthTest();
	BaseLoadContent();
	LoadContent();
	liClock delta_clock;
	delta_clock.Start();
	float dt = 0;
	while (Sys_IsRunning() && !closed) {
		MiscRendererFunctions::Clear();
		
		Render3D(dt);
		Update(dt);
		PostProcess(dt);
		RenderGUI(dt);

		dt = delta_clock.DeltaTime();
		Sys_PollWindow();
	}
	UnloadContent();
}

float liGame::GetAspectRatio() const
{
	return Sys_GetAspectRatio();
}

int32_t liGame::GetWidth() const
{
	return Sys_GetWidth();
}

int32_t liGame::GetHeight() const
{
	return Sys_GetHeight();
}

bool liGame::IsKeyDown(ubyte key) const
{
	return Sys_IsKeyDown(key) == true;
}

bool liGame::IsKeyUp(ubyte key) const
{
	return Sys_IsKeyDown(key) == false;
}

bool liGame::IsMButtonDown(ubyte mbutton) const
{
	return Sys_IsMButtonDown(mbutton) == true;
}

bool liGame::IsMButtonUp(ubyte mbutton) const
{
	return Sys_IsMButtonDown(mbutton) == false;
}

short liGame::GetMouseX() const
{
	return Sys_GetMouseX();
}

short liGame::GetMouseY() const
{
	return Sys_GetMouseY();
}

void liGame::LockCursor() const
{
	Sys_HideCursor();
	Sys_LockCursor();
}

void liGame::UnlockCursor()
{
	Sys_ShowCursor();
	Sys_FreeCursor();
}

void liGame::Close()
{
	this->closed = true;
}