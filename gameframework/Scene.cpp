#include "Scene.h"
#include <glrenderer/MiscFunctions.h>
#include <glrenderer/ScreenQuad.h>
#include <gameframework/ShaderAsset.h>
#include "ActorSerializer.h"
#include <platform/win32/Win32Header.h>

using namespace tinyxml2;

liScene::liScene(liContentManager* content, liVector2i screen, liString name)
{
	this->content = content;
	this->name = name;
	Initialize(screen);
}

liScene::~liScene()
{
	Shutdown();
}

void liScene::Initialize(liVector2i screen)
{
	actor3d_shader = liShaderAsset::CreateShader(content->LoadAsset<liShaderAsset>("quad.vsh"), content->LoadAsset<liShaderAsset>("actor3d.fsh"), { "position" });
	font_shader = liShaderAsset::CreateShader(content->LoadAsset<liShaderAsset>("font.vsh"), content->LoadAsset<liShaderAsset>("font.fsh"), { "position" });
	gui_shader = liShaderAsset::CreateShader(content->LoadAsset<liShaderAsset>("gui.vsh"), content->LoadAsset<liShaderAsset>("gui.fsh"), { "position", "textures" });

	quad = new ScreenQuadRenderer(content);
	renderer = new DeferredRenderer(screen, content);
}

void liScene::Shutdown()
{
	actors.DeleteDataPointers();
	delete quad;
	delete renderer;
	delete actor3d_shader;
	delete font_shader;
	delete gui_shader;
}

liList<liActor*>* liScene::GetActors()
{
	return &actors;
}

void liScene::Write(liFileSystem* fs)
{
	this->fileptr = fs->AddFile(name + ".scene");
	XMLPrinter printer;
	printer.OpenElement("Scene");

	printer.OpenElement("Name");
	printer.PushText(name.c_str());
	printer.CloseElement();

	printer.OpenElement("ActorCount");
	printer.PushText(actors.Size());
	printer.CloseElement();
	
	for (size_t i = 0; i < actors.Size(); i++) {
		printer.OpenElement("Actor");
		ActorSerializer::SerializeActor(actors[i], printer);
		printer.CloseElement();
	}

	printer.CloseElement();

	fileptr->BeginWrite();
	fileptr->WriteString(printer.CStr());
	fileptr->Close();
}

void liScene::AddActor(liActor* actor)
{
	actors.Push(actor);
}

void liScene::SpawnAll()
{
	for (size_t i = 0; i < actors.Size(); i++) {
		actors[i]->Spawn();
	}
}

RenderShader* liScene::GetActor3DShader()
{
	return actor3d_shader;
}

RenderShader* liScene::GetFontShader()
{
	return font_shader;
}

RenderShader* liScene::GetGUIShader()
{
	return gui_shader;
}

void liScene::SetMainCamera(liCamera* maincamera)
{
	this->maincamera = maincamera;
}

liCamera* liScene::GetMainCamera()
{
	return maincamera;
}

void liScene::LoadMatrices()
{
	MiscRendererFunctions::LoadMatrices(actor3d_shader->GetProgram(), maincamera->GetProjectionMatrix(), maincamera->GetViewMatrix());
	MiscRendererFunctions::LoadMatrices(font_shader->GetProgram(), gui_projection, maincamera->GetViewMatrix());
	MiscRendererFunctions::LoadMatrices(gui_shader->GetProgram(), gui_projection, maincamera->GetViewMatrix());
}

void liScene::Render3D()
{
	auto render_actors = [](liList<liActor*>* actors, RenderShader* shader) {
		for (size_t i = 0; i < actors->Size(); i++) {
			auto actor = actors->At(i);
			if (actor->IsActive()) {
				if (actor->GetFlag() == liActorFlag::FLAG_3D) {
					actor->Render(shader);
				}
			}
		}
	};
	renderer->Render(render_actors, &actors, actor3d_shader);
}

void liScene::RenderGUI()
{
	MiscRendererFunctions::Prepare2D();
	for (size_t i = 0; i < actors.Size(); i++) {
		if (actors[i]->IsActive()) {
			if (actors[i]->GetFlag() == liActorFlag::FLAG_GUI) {
				RenderShader* shader = gui_shader;
				if (actors[i]->GetType() == liActorType::TYPE_LABEL) {
					shader = font_shader;
				}
				actors[i]->Render(shader);
			}
		}
	}
	MiscRendererFunctions::Close2D();
}

void liScene::PostProcess()
{
}

void liScene::UpdateAll()
{
	for (size_t i = 0; i < actors.Size(); i++) {
		actors[i]->Update();
	}
	liLightingEngine::LoadLighting(actor3d_shader, &lights, maincamera->transform.position);
	renderer->Update(maincamera);
	this->gui_projection = liMatrix4x4::Orthographic(0, Sys_GetWidth(), Sys_GetHeight(), 0, 0, 1.0f);
}

liContentManager* liScene::GetContentManager()
{
	return content;
}

liActor* liScene::GetActor(int index)
{
	return actors[index];
}

liMatrix4x4 liScene::GetGUIProjection()
{
	return gui_projection;
}

void liScene::GenerateNewIdentifiers()
{
	for (size_t i = 0; i < actors.Size(); i++) {
		actors[i]->SetGUID(LiLib_GenerateGUID());
	}
}

liList<liLight*>* liScene::GetLights()
{
	return &lights;
}

void liScene::AddLight(liActor* actor)
{
	if (actor->GetType() == liActorType::TYPE_LIGHT) {
		lights.Push((liLight*)actor);
		actors.Push(actor);
	}
	for (int i = 0; i < actor->GetChildren()->Size(); i++) {
		auto child = actor->GetChildren()->At(i);
		AddLight(child);
	}
}

DeferredRenderer* liScene::GetRenderer()
{
	return renderer;
}

void liScene::Present()
{
	MiscRendererFunctions::DirectBindTexture(renderer->GetFinalTexture(), 0);
	quad->Present();
	MiscRendererFunctions::DirectBindTexture(0);
}

liScene* liScene::Load(liVector2i screen, liContentManager* content, liFile* fileptr)
{
	liScene* scene = new liScene(content, screen, "Scene");
	scene->fileptr = fileptr;
	XMLDocument doc;
	liString filedata = fileptr->Read();
	doc.Parse(filedata.c_str());
	auto scene_element = doc.FirstChildElement("Scene");
	scene->SetName(scene_element->FirstChildElement("Name")->GetText());
	scene->actors.Resize(scene_element->FirstChildElement("ActorCount")->Unsigned64Text());
	for (XMLElement* node = scene_element->FirstChildElement("Actor"); node; node = node->NextSiblingElement("Actor")) {
		scene->AddActor(ActorSerializer::DeserializeActor(scene, node));
	}
	return scene;
}