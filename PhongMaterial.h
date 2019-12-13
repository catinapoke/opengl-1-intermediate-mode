#pragma once
#include <fstream>
#include <iostream>
#include "Material.h"
#include "basicOpengl.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/istreamwrapper.h"

using vec4 = glm::vec4;
using vec3 = glm::vec3;
// КЛАСС ДЛЯ РАБОТЫ С МАТЕРИАЛОМ, ИСПОЛЬЗУЮЩИМ РАСЧЕТ ОСВЕЩЕНИЯ ПО ФОНГУ 
class PhongMaterial : public Material  
{
public:
	// конструктор по умолчанию 
	PhongMaterial();
	PhongMaterial(PhongMaterial* otherMaterial);
	PhongMaterial(const char* filename);
	PhongMaterial::PhongMaterial(vec4 ambient, vec4 diffuse, vec4 specular, vec4 emission, float shininess);
	// задание параметров материала 
	void setAmbient(vec4 color);
	void setDiffuse(vec4 color);
	void setSpecular(vec4 color);
	void setEmission(vec4 color);   
	void setShininess(float p);

	bool isTransparent();

	// загрузка параметров материала из внешнего текстового файла   
	virtual void load(const char* filename);

	// установка всех параметров материала 
	virtual void apply();
protected:
	// фоновая составляющая  
	vec4 ambient;
	// диффузная составляющая 
	vec4 diffuse;
	// зеркальная составляющая 
	vec4 specular;
	// самосвечение 
	vec4 emission;
	// степень отполированности 
	float shininess;
	// Прозрачность
	bool transparent;

	virtual void MaterialParse(rapidjson::Value& node);
};