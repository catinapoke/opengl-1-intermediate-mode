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
// ����� ��� ������ � ����������, ������������ ������ ��������� �� ����� 
class PhongMaterial : public Material  
{
public:
	// ����������� �� ��������� 
	PhongMaterial();
	PhongMaterial(PhongMaterial* otherMaterial);
	PhongMaterial(const char* filename);
	PhongMaterial::PhongMaterial(vec4 ambient, vec4 diffuse, vec4 specular, vec4 emission, float shininess);
	// ������� ���������� ��������� 
	void setAmbient(vec4 color);
	void setDiffuse(vec4 color);
	void setSpecular(vec4 color);
	void setEmission(vec4 color);   
	void setShininess(float p);

	bool isTransparent();

	// �������� ���������� ��������� �� �������� ���������� �����   
	virtual void load(const char* filename);

	// ��������� ���� ���������� ��������� 
	virtual void apply();
protected:
	// ������� ������������  
	vec4 ambient;
	// ��������� ������������ 
	vec4 diffuse;
	// ���������� ������������ 
	vec4 specular;
	// ������������ 
	vec4 emission;
	// ������� ���������������� 
	float shininess;
	// ������������
	bool transparent;

	virtual void MaterialParse(rapidjson::Value& node);
};