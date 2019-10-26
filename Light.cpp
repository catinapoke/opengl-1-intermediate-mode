#include "Light.h"

Light::Light() :Light(vec3(0, 0, 0))
{
}

Light::Light(vec3 position)
{
	setPosition(vec4(position.x, position.y, position.z, 1.0));
	setAmbient(vec4(1.0, 1.0, 1.0, 1.0));
	setDiffuse(vec4(0.0, 0.0, 0.0, 1.0));
	setSpecular(vec4(0.0, 0.0, 0.0, 1.0));
}

Light::Light(float x, float y, float z) :Light(vec3(x, y, z))
{
}

Light::Light(const char* filename)
{
	load(filename);
}

void Light::setAmbient(vec4 color)
{
	ambient = color;
}

void Light::setDiffuse(vec4 color)
{
	diffuse = color;
}

void Light::setSpecular(vec4 color)
{
	ambient = color;
}

void Light::setPosition(vec4 pos)
{
	position = pos;
}

void Light::setPosition(glm::vec3 pos)
{
	position.x = pos.x;
	position.y = pos.y;
	position.z = pos.z;
	position.w = 1;
}

void Light::load(const char* jsonfile)
{
	std::ifstream ifs(jsonfile);
	if (!ifs.is_open())
	{
		std::cerr << "Couldn't open file " << jsonfile << "for reading \n";
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

	position = vec4(
		doc["position"][0].GetDouble(),
		doc["position"][1].GetDouble(),
		doc["position"][2].GetDouble(),
		doc["position"][3].GetDouble()
	);

	//Close the file
	ifs.close();
}

void Light::apply(GLenum light)
{
	glEnable(light);
	glLightfv(light, GL_AMBIENT, glm::value_ptr(ambient));
	glLightfv(light, GL_DIFFUSE, glm::value_ptr(diffuse));
	glLightfv(light, GL_SPECULAR, glm::value_ptr(specular));
	glLightfv(light, GL_POSITION, glm::value_ptr(position));
}