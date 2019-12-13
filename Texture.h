#pragma once
#include "basicOpengl.h"
#include "IL\il.h"
#include "IL\ilu.h"
#include "IL\ilut.h"
// ����� ��� ������ � ���������
class Texture
{
public:
	Texture();
	Texture(const char* filename);
	void load(const char* filename); // �������� �������� �� �������� �����
	void apply(GLenum texUnit = GL_TEXTURE0); // ���������� �������� (�������� � ����������� ����� � ��������� ����������)
	static void disableAll(); // ���������� ��������������� ��� ���� ���������� ������
	static int texFilterMode; // ����� ���������� ��� ���� �������:
						// ��������, ����������, ��������� ������, �����������, ������������ �2 � �.�.
private:
	// ������������� (������) ����������� �������
	GLuint texIndex;
	static void SetTextureMode(int mode);
};