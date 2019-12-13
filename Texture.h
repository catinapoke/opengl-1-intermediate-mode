#pragma once
#include "basicOpengl.h"
#include "IL\il.h"
#include "IL\ilu.h"
#include "IL\ilut.h"
// КЛАСС ДЛЯ РАБОТЫ С ТЕКСТУРОЙ
class Texture
{
public:
	Texture();
	Texture(const char* filename);
	void load(const char* filename); // загрузка текстуры из внешнего файла
	void apply(GLenum texUnit = GL_TEXTURE0); // применение текстуры (привязка к текстурному блоку и установка параметров)
	static void disableAll(); // отключение текстурирования для всех текстурных блоков
	static int texFilterMode; // режим фильтрации для всех текстур:
						// точечная, билинейная, ближайший мипмап, трилинейная, анизатропная х2 и т.д.
private:
	// идентификатор (индекс) текстурного объекта
	GLuint texIndex;
	static void SetTextureMode(int mode);
};