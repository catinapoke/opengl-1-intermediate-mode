#pragma once
//#include "basicOpengl.h"
//#include <windows.h>
//#include <cstdio>
//#include <exception>

//#include <fstream>
//#include <iostream>
//#include <string>


// ������� ����� ��� ���� ����������
class Material
{
public:
	//"����������" ���������
	virtual void apply() = 0;
	// ����������� ����, �������� �� �������� ��������������
	virtual bool isTransparent()
	{
		return false;
	}
};