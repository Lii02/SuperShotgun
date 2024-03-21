#include <gameframework/Game.h>
#include <platform/InputCodes.h>
#include <lilib/Misc.h>
#include <glrenderer/Texture2D.h>
#include <glrenderer/MiscFunctions.h>
#include <gameframework/ShaderAsset.h>
#include <gameframework/Scene.h>
#include <gameframework/image/bmp.h>
#include <gameframework/fonts/ttf.h>
#include <gameframework/Label.h>
#include <gameframework/GUITexture.h>
#include <gameframework/GUIButton.h>

#define MAX_LIGHTS 50

class FPSGame : public liGame {
private:
	liScene* scene;
	liTTF* arial, *consolas;
	float cameraspeed = 50;
	liLight* sun;
public:
	void AddLight() {
		if (scene->GetLights()->Size() < MAX_LIGHTS) {
			liVector3f scale = scene->GetActor(1)->transform.scale;
			liVector3f half = scale / liVector3f(2, 2, 2);
			liVector3f color = liVector3f(1, 1, 1);
			liLight* light = new liLight(liLightType::TYPE_POINT, color, 75, 100, 0, 0.5f);
			light->transform.position = liVector3f(LiLib_RandomFloat(scale.x) - half.x, 15, LiLib_RandomFloat(scale.z) - half.z);
			scene->AddLight(light);
		}
	}

	virtual void Render3D(float dt) override
	{
		scene->Render3D();
	}

	virtual void RenderGUI(float dt) override
	{
		scene->RenderGUI();
	}

	virtual void Update(float dt) override
	{
		liCamera* maincamera = scene->GetMainCamera();

		if (IsKeyDown(KEY_W)) {
			maincamera->transform.position.z -= cameraspeed * dt;
		}
		else if (IsKeyDown(KEY_A)) {
			maincamera->transform.position.x -= cameraspeed * dt;
		}
		else if (IsKeyDown(KEY_S)) {
			maincamera->transform.position.z += cameraspeed * dt;
		}
		else if (IsKeyDown(KEY_D)) {
			maincamera->transform.position.x += cameraspeed * dt;
		}

		if (IsKeyDown(KEY_UP)) {
			maincamera->transform.rotation.x -= cameraspeed * dt;
		}
		else if (IsKeyDown(KEY_LEFT)) {
			maincamera->transform.rotation.y -= cameraspeed * dt;
		}
		else if (IsKeyDown(KEY_DOWN)) {
			maincamera->transform.rotation.x += cameraspeed * dt;
		}
		else if (IsKeyDown(KEY_RIGHT)) {
			maincamera->transform.rotation.y += cameraspeed * dt;
		}

		if (IsKeyDown(KEY_SPACE)) {
			maincamera->transform.position.y += cameraspeed * dt;
		}
		else if (IsKeyDown(KEY_LSHIFT)) {
			maincamera->transform.position.y -= cameraspeed * dt;
		}

		if (IsKeyDown(KEY_ESCAPE)) {
			Close();
		}

		if (IsKeyDown(KEY_H)) {
			AddLight();
		}

		scene->UpdateAll();
		scene->LoadMatrices();
	}

	virtual void PostProcess(float dt) override
	{
		scene->PostProcess();
		scene->Present();
	}

	virtual void LoadContent() override
	{
		//fs->PrintFS();
		this->scene = liScene::Load({ GetWidth(), GetHeight() }, content, fs->FindFile("UnnamedScene.scene"));
		scene->GenerateNewIdentifiers();
		scene->Write(fs->FindFolder("scenes"));
		arial = content->LoadAsset<liTTF>("arial.ttf");
		consolas = content->LoadAsset<liTTF>("consolas.ttf");

		MiscRendererFunctions::EnableBlending();
		MiscRendererFunctions::SetAlphaBlending(AlphaBlendingFunc::ONE_MINUS_SRC);
		MiscRendererFunctions::EnableBackfaceCulling();

		sun = new liLight(liLightType::TYPE_DIRECTIONAL, liVector3f(1, 1, 1), 1);
		sun->transform.rotation = liVector3f(60, -50, 0);
		scene->AddLight(sun);

		for (int i = 0; i < scene->GetRenderer()->GetGBufferTextures().Size(); i++) {
			uint32_t texture = scene->GetRenderer()->GetGBufferTextures()[i];
			int size = 64;
			liGUITexture* gui = new liGUITexture(new Texture2D(texture));
			gui->transform.scale = liVector3f(size, size, 1);
			gui->transform.position = liVector3f(size + (size * i * 2), size + (size / 2), 0);
			scene->AddActor(gui);
		}

		LockCursor();
	}

	virtual void UnloadContent() override
	{
		delete scene;
	}
};

int main(int argc, char** argv) {
	FPSGame game;
	game.Startup("upgraded-pancake", 1280, 720);
	game.Run();
	game.Shutdown();
	return 0;
}