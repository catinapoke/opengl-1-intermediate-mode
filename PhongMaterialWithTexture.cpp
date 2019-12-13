#include "PhongMaterialWithTexture.h"

PhongMaterialWithTexture::PhongMaterialWithTexture():PhongMaterial()
{

}

PhongMaterialWithTexture::PhongMaterialWithTexture(PhongMaterialWithTexture* otherMaterial):PhongMaterial(otherMaterial)
{
	printf("Copy damn phong material with texture\n");
	texture = otherMaterial->texture;
}

PhongMaterialWithTexture::PhongMaterialWithTexture(const char* filename)
{
	load(filename);
}

PhongMaterialWithTexture::PhongMaterialWithTexture(vec4 _ambient, vec4 _diffuse, vec4 _specular, vec4 _emission, float _shininess, 
	const char* textureFileName):PhongMaterial(_ambient, _diffuse, _specular, _emission, _shininess)
{
	texture = new Texture(textureFileName);
}

void PhongMaterialWithTexture::setTexture(Texture* _texture)
{
	texture = _texture;
}

void PhongMaterialWithTexture::apply()
{
	//printf("Apply damn material\n");
	PhongMaterial::apply();
	texture->apply(GL_TEXTURE0); // привязываем текстуру
}

void PhongMaterialWithTexture::load(const char* filename)
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
	PhongMaterialWithTexture::MaterialParse(doc);

	//Close the file
	ifs.close();
}

void PhongMaterialWithTexture::MaterialParse(rapidjson::Value& node)
{
	PhongMaterial::MaterialParse(node);
	std::string texturePath = "textures/";
	texturePath +=node["texture"].GetString();
	setTexture(new Texture(texturePath.c_str()));
}