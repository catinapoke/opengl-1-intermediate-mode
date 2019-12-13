#pragma once
#include "PhongMaterial.h"
#include "Texture.h"

class PhongMaterialWithTexture : public PhongMaterial
{
public:
	// ����������� �� ���������
	PhongMaterialWithTexture();
	PhongMaterialWithTexture(PhongMaterialWithTexture* otherMaterial);
	PhongMaterialWithTexture(const char* filename);
	PhongMaterialWithTexture::PhongMaterialWithTexture(vec4 ambient, vec4 diffuse, vec4 specular, vec4 emission, float shininess, const char* textureFileName);
	
	void setTexture(Texture* texture);// ��������� ������������ ��������
	void load(const char* filename);
	void apply();// ��������� ���� ���������� ���������

private:
	void MaterialParse(rapidjson::Value& node);
	// ������������ ��������
	Texture* texture;
};