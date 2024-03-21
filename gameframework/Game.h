#ifndef FRAMEWORK_GAME_H
#define FRAMEWORK_GAME_H
#include <lilib/EngineDefs.h>
#include <lilib/LiString.h>
#include "FileSystem.h"
#include "ContentManager.h"

class liGame {
protected:
	liFileSystem* fs, *crash_logs, *config_files;
	liContentManager* content;
private:
	bool closed;
	void BaseLoadContent();
public:
	liGame();
	virtual ~liGame();
	void Startup(liString title, int width, int height);
	void Shutdown();
	void Run();
	virtual void LoadContent() = 0;
	virtual void UnloadContent() = 0;
	float GetAspectRatio() const;
	int32_t GetWidth() const;
	int32_t GetHeight() const;
	bool IsKeyDown(ubyte key) const;
	bool IsKeyUp(ubyte key) const;
	bool IsMButtonDown(ubyte mbutton) const;
	bool IsMButtonUp(ubyte mbutton) const;
	short GetMouseX() const;
	short GetMouseY() const;
	void LockCursor() const;
	void UnlockCursor();
	void Close();

	virtual void Render3D(float dt) = 0;
	virtual void RenderGUI(float dt) = 0;
	virtual void Update(float dt) = 0;
	virtual void PostProcess(float dt) = 0;
};

#endif