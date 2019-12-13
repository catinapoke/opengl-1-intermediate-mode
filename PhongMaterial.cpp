#include "PhongMaterial.h"

PhongMaterial::PhongMaterial()
{
	setAmbient(vec4(1.0, 0.0, 0.0, 1.0));
	setDiffuse(vec4(0.4, 0.0, 0.0, 1.0));
	setSpecular(vec4(1.0, 1.0, 1.0, 1.0));
	setEmission(vec4(0.0, 0.0, 0.0, 1.0));
	setShininess(64.0f);
	transparent = false;
}

PhongMaterial::PhongMaterial(PhongMaterial* otherMaterial)
{
	setAmbient(otherMaterial->ambient);
	setDiffuse(otherMaterial->diffuse);
	setSpecular(otherMaterial->specular);
	setEmission(otherMaterial->emission);
	setShininess(otherMaterial->shininess);
	transparent = otherMaterial->transparent;
}

PhongMaterial::PhongMaterial(vec4 _ambient, vec4 _diffuse, vec4 _specular, vec4 _emission, float _shininess)
{
	ambient = _ambient;
	diffuse = _diffuse;
	specular = _specular;
	emission = _emission;
	shininess = _shininess;
	transparent = (diffuse.a != 1.0f);
}

PhongMaterial::PhongMaterial(const char* filename)
{
	load(filename);
}

void PhongMaterial::setAmbient(glm::vec4 color)
{
	ambient = color;
}

void PhongMaterial::setDiffuse(glm::vec4 color)
{
	diffuse = color;
}

void PhongMaterial::setSpecular(glm::vec4 color)
{
	specular = color;
}

void PhongMaterial::setEmission(glm::vec4 color)
{
	emission = color;
}

void PhongMaterial::setShininess(float p)
{
	shininess = p;
}

bool PhongMaterial::isTransparent()
{
	return transparent;
}

void PhongMaterial::load(const char* filename)
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

	MaterialParse(doc);

	//Close the file
	ifs.close();
}

void PhongMaterial::apply()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(ambient));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(diffuse));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(specular));
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(emission));
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}

void PhongMaterial::MaterialParse(rapidjson::Value& node)
{
	ambient = vec4(
		node["ambient"][0].GetDouble(),
		node["ambient"][1].GetDouble(),
		node["ambient"][2].GetDouble(),
		node["ambient"][3].GetDouble()
	);

	diffuse = vec4(
		node["diffuse"][0].GetDouble(),
		node["diffuse"][1].GetDouble(),
		node["diffuse"][2].GetDouble(),
		node["diffuse"][3].GetDouble()
	);

	specular = vec4(
		node["specular"][0].GetDouble(),
		node["specular"][1].GetDouble(),
		node["specular"][2].GetDouble(),
		node["specular"][3].GetDouble()
	);

	emission = vec4(
		node["emission"][0].GetDouble(),
		node["emission"][1].GetDouble(),
		node["emission"][2].GetDouble(),
		node["emission"][3].GetDouble()
	);

	shininess = node["shininess"].GetDouble();
	transparent = (diffuse.a != 1.0f);
}