#ifndef FRAMEWORK_SCENE_H
#define FRAMEWORK_SCENE_H
#include <lilib/EngineDefs.h>
#include <lilib/LiString.h>
#include <gameframework/Actor.h>
#include <gameframework/FileSystem.h>
#include <gameframework/ContentManager.h>
#include <glrenderer/RenderShader.h>
#include <glrenderer/Framebuffer.h>
#include <gameframework/Camera.h>
#include <gameframework/HDR.h>
#include "XMLHelper.h"
#include "LightingEngine.h"
#include "Deferred.h"

class liScene : public liAsset {
private:
	liContentManager* content;
	liList<liActor*> actors;
	RenderShader* actor3d_shader, *gui_shader, *font_shader;
	liCamera* maincamera;
	liMatrix4x4 gui_projection;
	liList<liLight*> lights;
	DeferredRenderer* renderer;
	ScreenQuadRenderer* quad;
public:
	liScene(liContentManager* content, liVector2i screen, liString name = "UnnamedScene");
	~liScene();

	void Initialize(liVector2i screen);
	void Shutdown();
	liList<liActor*>* GetActors();
	void Write(liFileSystem* fs);
	void AddActor(liActor* actor);
	void SpawnAll();
	RenderShader* GetActor3DShader();
	RenderShader* GetFontShader();
	RenderShader* GetGUIShader();
	void SetMainCamera(liCamera* maincamera);
	liCamera* GetMainCamera();
	void LoadMatrices();
	void Render3D();
	void RenderGUI();
	void PostProcess();
	void UpdateAll();
	liContentManager* GetContentManager();
	liActor* GetActor(int index);
	liMatrix4x4 GetGUIProjection();
	void GenerateNewIdentifiers();
	liList<liLight*>* GetLights();
	void AddLight(liActor* actor);
	DeferredRenderer* GetRenderer();
	void Present();

	static liScene* Load(liVector2i screen, liContentManager* content, liFile* fileptr);
};

#endif