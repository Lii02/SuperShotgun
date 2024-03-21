#ifndef GAMEFRAMEWORK_ACTORSERIALIZER_H
#define GAMEFRAMEWORK_ACTORSERIALIZER_H
#include <lilib/EngineDefs.h>
#include "Material.h"
#include "Actor.h"
#include <thirdparty/tinyxml2.h>
#include "Scene.h"

class ActorSerializer {
public:
	static void SerializeMaterialValue(liMaterialValue* value, cstring material_name, tinyxml2::XMLPrinter& printer);
	static void SerializeActor(liActor* actor, tinyxml2::XMLPrinter& printer);
	static void DeserializeMaterialValue(liScene* scene, liMaterial* material, liMaterialValue* material_value, cstring name, tinyxml2::XMLElement* element);
	static liActor* DeserializeActor(liScene* scene, tinyxml2::XMLElement* element);
};

#endif