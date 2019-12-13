#pragma once
#include "GameObjectFactory.h"

void GameObjectFactory::init(std::string jsonfile)
{
	LoadSceneJSON(jsonfile);
}

std::shared_ptr<GameObject> GameObjectFactory::create(GameObjectType type, int x, int y)
{
	std::shared_ptr<GameObject> gameObject;
	if (type == GameObjectType::PORTAL_1_OBJECT || type == GameObjectType::PORTAL_2_OBJECT)
	{
		std::shared_ptr<Portal> portalObj = std::make_shared<Portal>(glm::ivec2(x, y), type);// new Portal(
		gameObject = std::dynamic_pointer_cast<GameObject>(portalObj);
	}	 
	else if (type == GameObjectType::BOMB_OBJECT)
	{
		std::shared_ptr<Bomb> bombObj = std::make_shared<Bomb>(glm::ivec2(x, y), type);// new Bomb(
		gameObject = std::dynamic_pointer_cast<GameObject>(bombObj);
	}
	else if (type == GameObjectType::MONSTER_OBJECT)
	{
		std::shared_ptr<Monster> monsterObj = std::make_shared<Monster>(glm::ivec2(x, y), std::make_pair(ivec2(x, y), GetRandomEmptyPos()));// new Monster(
		gameObject = std::dynamic_pointer_cast<GameObject>(monsterObj);
	}
	else
		gameObject = std::make_shared<GameObject>(glm::ivec2(x, y), type);

	gameObject->setGraphicObject(templateObjects[static_cast<int>(type)]);
	return gameObject;
}

void GameObjectFactory::LoadSceneJSON(std::string filename)
{
	std::ifstream ifs(filename);
	if (!ifs.is_open())
	{
		std::cerr << "Couldn't open file " << filename << "for reading \n";
		return;
	}

	//Read from file
	rapidjson::IStreamWrapper isw(ifs);
	rapidjson::Document doc;
	doc.ParseStream(isw);
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);

	if (doc.HasParseError())
	{
		std::cerr << "Filename: " << filename << "\n";
		std::cerr << "Parse error: " << doc.GetParseError() << "\n Offset: " << doc.GetErrorOffset() << "\n";
		return;
	}

	const rapidjson::Value& membersObject = doc["AllObjectsDescription"];
	std::cout << "Scene members: \n";
	for (rapidjson::Value::ConstMemberIterator it = membersObject.MemberBegin(); it != membersObject.MemberEnd(); it++) {
		std::cout << it->name.GetString() <<"\n";
		ParseObject(it);
	}

	//Close the file
	ifs.close();
}

void GameObjectFactory::ParseObject(rapidjson::Value::ConstMemberIterator it)
{
	GameObjectType objectType = ParseObjectType(it->name.GetString());
	std::string meshPath = "meshes/";
	meshPath += it->value["Mesh"]["FileName"].GetString();
	Mesh mesh(meshPath.c_str());

	vec4 ambient(
		it->value["Material"]["PhongParameters"]["ambient"][0].GetDouble(),
		it->value["Material"]["PhongParameters"]["ambient"][1].GetDouble(),
		it->value["Material"]["PhongParameters"]["ambient"][2].GetDouble(),
		it->value["Material"]["PhongParameters"]["ambient"][3].GetDouble()
	);
	vec4 diffuse(
		it->value["Material"]["PhongParameters"]["diffuse"][0].GetDouble(),
		it->value["Material"]["PhongParameters"]["diffuse"][1].GetDouble(),
		it->value["Material"]["PhongParameters"]["diffuse"][2].GetDouble(),
		it->value["Material"]["PhongParameters"]["diffuse"][3].GetDouble()
	);
	vec4 specular(
		it->value["Material"]["PhongParameters"]["specular"][0].GetDouble(),
		it->value["Material"]["PhongParameters"]["specular"][1].GetDouble(),
		it->value["Material"]["PhongParameters"]["specular"][2].GetDouble(),
		it->value["Material"]["PhongParameters"]["specular"][3].GetDouble()
	);
	vec4 emission(
		it->value["Material"]["PhongParameters"]["emission"][0].GetDouble(),
		it->value["Material"]["PhongParameters"]["emission"][1].GetDouble(),
		it->value["Material"]["PhongParameters"]["emission"][2].GetDouble(),
		it->value["Material"]["PhongParameters"]["emission"][3].GetDouble()
	);
	double shininess = it->value["Material"]["PhongParameters"]["shininess"].GetDouble();

	Material *material;
	std::string materialType = it->value["Material"]["Type"].GetString();
	//printf("Material type of %s: \"%s\"\n" ,it->name.GetString() ,materialType.c_str());
	if (materialType == "PhongMaterialWithTexture")
	{
		std::string texturePath = "textures/";
		texturePath += it->value["Material"]["Texture"]["FileName"].GetString();
		material = new PhongMaterialWithTexture(ambient, diffuse, specular, emission, shininess, texturePath.c_str());
	}
	else
	{
		material = new PhongMaterial(ambient, diffuse, specular, emission, shininess);
	}
		

	templateObjects[static_cast<int>(objectType)] = GraphicObject(material, &mesh);
}