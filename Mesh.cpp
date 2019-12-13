#include "Mesh.h"

void handleSeparator(char separator, char received)
{
	if (received != separator)
	{
		char str[26];
		sprintf_s(str, "Expected '%c', but got '%c'", separator, received);
		throw std::exception(str);
	}
}

Mesh::Mesh()
{
}

Mesh::Mesh(Mesh* m) : Mesh()
{
	vertices = m->vertices;
	vertexCount = m->vertexCount;
	indices = m->indices;
	LoadBuffers();
}

Mesh::Mesh(const char* filename)
{
	load(filename);
}

std::string ivec3ToString(ivec3 vec)
{
	char buffer[256];
	sprintf_s(buffer, "%i/%i/%i", vec.x, vec.y, vec.z);
	return std::string(buffer);
}

void Mesh::load(const char* filename)
{
	std::ifstream f;
	f.open(filename);
	if (!f.is_open()) {
		printf("Cannot open file %s\n", filename);
		return;
	};

	// First word in line
	std::string s;
	// Line residue
	char temp[512];
	// Coords
	std::vector<vec3> v;
	// Normals
	std::vector<vec3> vn;
	// Texture coords
	std::vector<vec3> vt;
	// Polygons
	std::vector<ivec3> faces;

	std::map<std::string, int> vertexToIndex;

	while (!f.eof()) {
		f >> s;
		if (s == "v") { // Coords
			vec3 vTemp;
			f >> vTemp.x;
			f >> vTemp.y;
			f >> vTemp.z;
			v.push_back(vTemp);
		}
		else if (s == "vn") { // Normals
			vec3 vnTemp;
			f >> vnTemp.x;
			f >> vnTemp.y;
			f >> vnTemp.z;
			vn.push_back(vnTemp);
		}
		else if (s == "vt") { // Textures
			vec3 vtTemp;
			f >> vtTemp.x;
			f >> vtTemp.y;
			f >> vtTemp.z;
			vt.push_back(vtTemp);
		}
		else if (s == "f") {
			for (int i = 0; i < 3; i++)
			{
				ivec3 fTemp;
				char temp_c;
				f >> fTemp.x;
				f >> temp_c;
				f >> fTemp.y;
				f >> temp_c;
				f >> fTemp.z;

				// Correction by start index in .obj files
				fTemp = ivec3(fTemp.x - 1, fTemp.y - 1, fTemp.z - 1);

				std::string tempStr = ivec3ToString(fTemp);

				auto vertex = vertexToIndex.find(tempStr);
				if (vertex != vertexToIndex.end())
				{
					indices.push_back((GLuint)(vertex->second));
				}
				else
				{
					faces.push_back(fTemp);
					indices.push_back((GLuint)(faces.size() - 1));
					vertexToIndex.insert(std::pair<std::string, int>(tempStr, (faces.size() - 1)));
				}
			}
		}
		f.getline(temp, 512);
	};
	f.close();

	vertexCount = faces.size();
	vertices = new Vertex[vertexCount];

	printf("Vertex count - %i\n Indices count - %i \n\n", vertexCount, indices.size());

	int k = 0;
	for (auto it = faces.begin(); it != faces.end(); it++)
	{
		vertices[k].coord[0] = v[(*it).x].x;
		vertices[k].coord[1] = v[(*it).x].y;
		vertices[k].coord[2] = v[(*it).x].z;

		vertices[k].textureCoord[0] = vt[(*it).y].x;
		vertices[k].textureCoord[1] = vt[(*it).y].y;
		vertices[k].textureCoord[2] = vt[(*it).y].z;

		vertices[k].normal[0] = vn[(*it).z].x;
		vertices[k].normal[1] = vn[(*it).z].y;
		vertices[k].normal[2] = vn[(*it).z].z;
		k++;
	}

	LoadBuffers();
}

void Mesh::LoadBuffers()
{
	if (BO[0] == 0 && BO[1] == 0)
	{
		glGenBuffers(2, BO);
	}

	glBindBuffer(GL_ARRAY_BUFFER, BO[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BO[1]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) *vertexCount, vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, BO[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BO[1]);
	glClientActiveTexture(GL_TEXTURE0);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, coord));
	glNormalPointer(GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glTexCoordPointer(3, GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textureCoord));

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}