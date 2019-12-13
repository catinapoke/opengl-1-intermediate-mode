#pragma once
//#include "basicOpengl.h"
//#include <windows.h>
//#include <cstdio>
//#include <exception>

//#include <fstream>
//#include <iostream>
//#include <string>


// БАЗОВЫЙ КЛАСС ДЛЯ ВСЕХ МАТЕРИАЛОВ
class Material
{
public:
	//"применение" материала
	virtual void apply() = 0;
	// определение того, является ли материал полупрозрачным
	virtual bool isTransparent()
	{
		return false;
	}
};