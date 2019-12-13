#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "basicOpengl.h"
#include "Vertex.h"

using vec3 = glm::vec3;
using ivec3 = glm::ivec3;

class Mesh
{
public:
	Mesh();
	Mesh(Mesh* m);
	Mesh(const char* filename);
	// Load mesh from file
	void load(const char* filename);
	void draw();

private:
	// Load mesh in buffers
	void LoadBuffers();
	Vertex* vertices;
	int vertexCount;
	std::vector<GLuint> indices;
	// Buffers: Vertex and indices
	GLuint BO[2] = { 0, 0 };
};