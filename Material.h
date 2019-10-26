#pragma once
#include "basicOpengl.h"

#include <fstream>
#include <iostream>
#include <string>
// Parsing library
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/istreamwrapper.h"

using vec4 = glm::vec4;
using vec3 = glm::vec3;

class Material
{
public:
	// Constructors
	Material();
	Material(Material* otherMaterial);
	Material(const char* filename);

	// Set material attributes
	void setAmbient(glm::vec4 color);
	void setDiffuse(glm::vec4 color);
	void setSpecular(glm::vec4 color);
	void setEmission(glm::vec4 color);
	void setShininess(float p);

	// Load material attributes from file
	void load(const char* filename);

	// apply material
	void apply();

private:
	// Material attributes 
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 emission;
	float shininess;
};