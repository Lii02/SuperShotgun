#include "ActorSerializer.h"
#include "XMLHelper.h"
#include <gameframework/Light.h>
#include <gameframework/Actor3D.h>
#include <gameframework/Actor2D.h>
#include <gameframework/Camera.h>
#include <gameframework/image/bmp.h>
#include <gameframework/models/obj.h>
#include <platform/win32/Win32Header.h>

using namespace tinyxml2;

void ActorSerializer::SerializeMaterialValue(liMaterialValue* value, cstring material_name, XMLPrinter& printer) {
	printer.OpenElement(material_name);
	XMLHelper::PrintGeneric<int>("Type", value->type, printer);
	if (value->type == liMaterialValueType::TYPE_COLOR) {
		XMLHelper::PrintVector3f("Color", value->color, printer);
	} else if(value->type == liMaterialValueType::TYPE_TEXTURE) {
		XMLHelper::PrintGeneric<cstring>("TexturePath", value->texture->GetFilepath().c_str(), printer);
	} else if (value->type == liMaterialValueType::TYPE_FLOAT) {
		XMLHelper::PrintGeneric<float>("Value", value->color.x, printer);
	}
	printer.CloseElement();
}

void ActorSerializer::SerializeActor(liActor* actor, XMLPrinter& printer) {
	printer.PushAttribute("Tag", actor->GetTag().c_str());
	printer.PushAttribute("IsActive", actor->IsActive());
	printer.PushAttribute("ChildrenCount", actor->GetChildren()->Size());
	printer.PushAttribute("Type", actor->GetType());
	printer.OpenElement("GUID");
	printer.PushText(actor->GetGUID().c_str());
	printer.CloseElement();
	
	printer.OpenElement("Transform");
	XMLHelper::PrintVector3f("Position", actor->transform.position, printer);
	XMLHelper::PrintVector3f("Rotation", actor->transform.rotation, printer);
	XMLHelper::PrintVector3f("Scale", actor->transform.scale, printer);
	printer.CloseElement();
	
	printer.OpenElement("ActorVariables");
	switch (actor->GetType()) {
		case liActorType::TYPE_ACTOR3D: {
			liActor3D* actor3D = (liActor3D*)actor;
			
			// Material
			SerializeMaterialValue(actor3D->GetMaterial()->GetValue(LIMATERIAL_DIFFUSE_UNIT), "DiffuseMaterial", printer);
			SerializeMaterialValue(actor3D->GetMaterial()->GetValue(LIMATERIAL_SPECULAR_UNIT), "SpecularMaterial", printer);

			printer.OpenElement("NormalMap");
			liMaterialNormalMap* nmap = actor3D->GetMaterial()->GetNormalMap();
			XMLHelper::PrintGeneric<bool>("UsesMap", nmap->uses_map, printer);
			if (nmap->uses_map) {
				XMLHelper::PrintGeneric<cstring>("TexturePath", nmap->texture->GetFilepath().c_str(), printer);
			}
			printer.CloseElement();

			auto mesh = actor3D->GetMesh();
			XMLHelper::PrintGeneric<cstring>("MeshPath", mesh->GetFilepath().c_str(), printer);
		} break;
		case liActorType::TYPE_CAMERA: {
			liCamera* camera = (liCamera*)actor;
			XMLHelper::PrintGeneric<int>("Type", camera->GetCameraType(), printer);
			XMLHelper::PrintGeneric<float>("FOV", camera->GetFOV(), printer);
			XMLHelper::PrintGeneric<float>("Far", camera->GetFar(), printer);
			XMLHelper::PrintGeneric<float>("Near", camera->GetNear(), printer);
			XMLHelper::PrintGeneric<bool>("IsMainCamera", camera->IsMainCamera(), printer);
		} break;
		case liActorType::TYPE_ACTOR2D: {
			liActor2D* actor2d = (liActor2D*)actor;
			auto sprite = actor2d->GetSprite();
			XMLHelper::PrintGeneric<cstring>("SpriteImagePath", sprite->GetImage()->GetFilepath().c_str(), printer);
		} break;
	}
	printer.CloseElement();
}

void ActorSerializer::DeserializeMaterialValue(liScene* scene, liMaterial* material, liMaterialValue* material_value, cstring name, XMLElement* element) {
	auto material_element = element->FirstChildElement(name);
	material_value->type = (liMaterialValueType)XMLHelper::ReadInt(material_element, "Type");
	switch (material_value->type) {
		case liMaterialValueType::TYPE_COLOR:
			material_value->color = XMLHelper::ReadVec3(material_element, "Color");
			break;
		case liMaterialValueType::TYPE_FLOAT:
			material_value->color.x = XMLHelper::ReadFloat(material_element, "Value");
			break;
		case liMaterialValueType::TYPE_TEXTURE:
			cstring texture_filepath = XMLHelper::ReadString(material_element, "TexturePath");
			// TODO Don't directly load images like this.
			material_value->texture = scene->GetContentManager()->LoadAsset<liBMP>(texture_filepath)->ToTexture();
			break;
	}
}

liActor* ActorSerializer::DeserializeActor(liScene* scene, XMLElement* element) {
	auto actor_tag = element->FindAttribute("Tag")->Value();
	auto actor_children_count = element->FindAttribute("ChildrenCount")->UnsignedValue();
	auto actor_type = (liActorType)element->FindAttribute("Type")->UnsignedValue();
	bool actor_active = element->FindAttribute("IsActive")->BoolValue();
	cstring guid = element->FirstChildElement("GUID")->GetText();
	liTransform transform;
	auto transform_element = element->FirstChildElement("Transform");
	transform.position = XMLHelper::ReadVec3(transform_element, "Position");
	transform.rotation = XMLHelper::ReadVec3(transform_element, "Rotation");
	transform.scale = XMLHelper::ReadVec3(transform_element, "Scale");
	auto actor_vars = element->FirstChildElement("ActorVariables");
	switch (actor_type) {
		case liActorType::TYPE_CAMERA: {
			liCamera* camera = new liCamera((liCameraType)XMLHelper::ReadInt(actor_vars, "Type"), XMLHelper::ReadFloat(actor_vars, "FOV"), Sys_GetAspectRatio(), XMLHelper::ReadFloat(actor_vars, "Far"), XMLHelper::ReadFloat(actor_vars, "Near"));
			camera->SetTag(actor_tag);
			camera->transform = transform;
			camera->SetGUID(guid);
			camera->Spawn();
			camera->SetActive(actor_active);
			camera->SetIsMainCamera(XMLHelper::ReadBool(actor_vars, "IsMainCamera"));
			if (camera->IsMainCamera())
				scene->SetMainCamera(camera);
			return camera;
		} break;
		case liActorType::TYPE_ACTOR3D: {
			liActor3D* actor3d = new liActor3D();
			actor3d->SetActive(actor_active);
			actor3d->SetTag(actor_tag);
			actor3d->transform = transform;
			actor3d->SetGUID(guid);
			actor3d->Spawn();
			
			// Mesh);
			auto mesh = actor3d->GetMesh();
			cstring mesh_filepath = XMLHelper::ReadString(actor_vars, "MeshPath");
			// TODO Don't directly load models like this.
			actor3d->SetMesh(scene->GetContentManager()->LoadAsset<liOBJ>(mesh_filepath)->ToMesh());
			
			// Material
			ActorSerializer::DeserializeMaterialValue(scene, actor3d->GetMaterial(), actor3d->GetMaterial()->GetValue(LIMATERIAL_DIFFUSE_UNIT), "DiffuseMaterial", actor_vars);
			ActorSerializer::DeserializeMaterialValue(scene, actor3d->GetMaterial(), actor3d->GetMaterial()->GetValue(LIMATERIAL_SPECULAR_UNIT), "SpecularMaterial", actor_vars);
			
			auto nmap_element = actor_vars->FirstChildElement("NormalMap");
			liMaterialNormalMap* value = actor3d->GetMaterial()->GetNormalMap();
			value->uses_map = (liMaterialValueType)XMLHelper::ReadBool(nmap_element, "UsesMap");
			if (value->uses_map) {
				cstring texture_filepath = XMLHelper::ReadString(nmap_element, "TexturePath");
				// TODO Don't directly load images like this.
				value->texture = scene->GetContentManager()->LoadAsset<liBMP>(texture_filepath)->ToTexture();
			}
			return actor3d;
		} break;
	}
	return nullptr;
}