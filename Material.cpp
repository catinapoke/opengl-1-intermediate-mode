#include "Material.h"

Material::Material()
{
	setAmbient(vec4(1.0, 0.0, 0.0, 1.0));
	setDiffuse(vec4(0.4, 0.0, 0.0, 1.0));
	setSpecular(vec4(1.0, 1.0, 1.0, 1.0));
	setEmission(vec4(0.0, 0.0, 0.0, 1.0));
	setShininess(64.0f);
}

Material::Material(Material* otherMaterial)
{
	setAmbient(otherMaterial->ambient);
	setDiffuse(otherMaterial->diffuse);
	setSpecular(otherMaterial->specular);
	setEmission(otherMaterial->emission);
	setShininess(otherMaterial->shininess);
}

Material::Material(const char* filename)
{
	load(filename);
}

void Material::setAmbient(glm::vec4 color)
{
	ambient = color;
}

void Material::setDiffuse(glm::vec4 color)
{
	diffuse = color;
}

void Material::setSpecular(glm::vec4 color)
{
	specular = color;
}

void Material::setEmission(glm::vec4 color)
{
	emission = color;
}

void Material::setShininess(float p)
{
	shininess = p;
}

void Material::load(const char* filename)
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

	ambient = vec4(
		doc["ambient"][0].GetDouble(),
		doc["ambient"][1].GetDouble(),
		doc["ambient"][2].GetDouble(),
		doc["ambient"][3].GetDouble()
	);

	diffuse = vec4(
		doc["diffuse"][0].GetDouble(),
		doc["diffuse"][1].GetDouble(),
		doc["diffuse"][2].GetDouble(),
		doc["diffuse"][3].GetDouble()
	);

	specular = vec4(
		doc["specular"][0].GetDouble(),
		doc["specular"][1].GetDouble(),
		doc["specular"][2].GetDouble(),
		doc["specular"][3].GetDouble()
	);

	emission = vec4(
		doc["emission"][0].GetDouble(),
		doc["emission"][1].GetDouble(),
		doc["emission"][2].GetDouble(),
		doc["emission"][3].GetDouble()
	);

	shininess = doc["shininess"].GetDouble();

	//Close the file
	ifs.close();
}

void Material::apply()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(ambient));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(diffuse));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(specular));
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(emission));
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}