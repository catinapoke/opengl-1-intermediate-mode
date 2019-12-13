#pragma once
#include <memory>
//#include "Data.h"
#include "GraphicObject.h"
#include "GameObject.h"
#include "Monster.h"
#include "PhongMaterial.h"
#include "PhongMaterialWithTexture.h"
// #include "pugixml/pugixml.hpp"

class GameObjectFactory
{
public:
	void init(std::string xmlfile); // Loading meshes and materials
	std::shared_ptr<GameObject> create(GameObjectType type, int x, int y);

private:
	void LoadSceneJSON(std::string filename);
	void ParseObject(rapidjson::Value::ConstMemberIterator it);

	GraphicObject templateObjects[static_cast<unsigned int>(GameObjectType::MAX_OBJECT_COUNT)];
};