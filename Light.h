#pragma once
#include <windows.h>
#include <cstdio>
#include <exception>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtc/type_ptr.hpp"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/istreamwrapper.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace rapidjson;

using vec3 = glm::vec3;
using vec4 = glm::vec4;
//using namespace glm;
// ����� ��� ������ � ���������� �����
class Light
{
public:
	// ������������
	Light();
	Light(glm::vec3 position);
	Light(float x, float y, float z);
	Light(const char* filename);

	// ������� ��������� ���������� ��������� �����   void setPosition (vec3 position);
	void setAmbient(glm::vec4 color);
	void setDiffuse(glm::vec4 color);
	void setSpecular(glm::vec4 color);
	void setPosition(glm::vec4 pos);
	void setPosition(glm::vec3 pos);
	void load(const char* jsonfile);
	void apply(GLenum light);
	// ��������� ���� ���������� ��������� ����� � �������� �������
	// ������ ������� ������ ���������� ����� ��������� ������,
	// �.�. ����� ��������������� ������� ��������� �����   void apply (GLenum LightNumber = GL_LIGHT0);

private:
	// ������� ��������� �����
	glm::vec4 position;
	// ������� ������������ ��������� �����
	glm::vec4 ambient;
	// ��������� ������������
	glm::vec4 diffuse;
	// ���������� ������������
	glm::vec4 specular;
};