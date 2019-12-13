#include "Texture.h"

int Texture::texFilterMode = 0;

Texture::Texture()
{
}

Texture::Texture(const char* filename)
{
	load(filename);
}

void Texture::load(const char* filename)
{
	glActiveTexture(GL_TEXTURE0); // Choise of active texture block
	glGenTextures(1, &texIndex); // Texture generation
	glBindTexture(GL_TEXTURE_2D, texIndex); // Texture binding
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); // Enable mipmap generation
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Set alignment
	GLubyte* pixels;

	ILuint imageId = ilGenImage();
	ilBindImage(imageId);
	//bool result = 
	if (!ilLoadImage(filename))
	{
		throw new std::exception("Can't load image");
	}
	// Get parameters
	int width = ilGetInteger(IL_IMAGE_WIDTH);
	int  height = ilGetInteger(IL_IMAGE_HEIGHT);
	int  format = ilGetInteger(IL_IMAGE_FORMAT);
	int  type = ilGetInteger(IL_IMAGE_TYPE);

	ILinfo ImageInfo;
	iluGetImageInfo(&ImageInfo);
	if (ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
	{
		iluFlipImage();
	}

	pixels = new GLubyte[width * height * 4];
	ilCopyPixels(0, 0, 0, width, height, 1, IL_RGBA, GL_UNSIGNED_BYTE, pixels);
	// Loading pixels into texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	ilDeleteImage(imageId);
	ilBindImage(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::apply(GLenum texUnit)
{
	glActiveTexture(texUnit); // выбираем активный текстурный блок
	glEnable(GL_TEXTURE_2D); // разрешаем текстурирование
	glBindTexture(GL_TEXTURE_2D, texIndex);
	SetTextureMode(texFilterMode);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // указываем режим наложения текстуры (GL_MODULATE)
}

void Texture::disableAll()
{
	int textureUnits = 0;
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &textureUnits);
	for (int i = 0; i < textureUnits; i++)
		glDisable(GL_TEXTURE0 + i);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

void Texture::SetTextureMode(int mode)
{
	const GLenum filters[] =		 { GL_TEXTURE_MIN_FILTER,    GL_TEXTURE_MAG_FILTER, GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT };
	const GLuint filterMode[9][3] = { {GL_NEAREST,			     GL_NEAREST,			1},  // 1)Точечная фильтрация;
									  {GL_LINEAR,			     GL_LINEAR,				1},  // 2)Билинейная фильтрация;
									  {GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR,				1},  // 3)Билинейная фильтрация с использованием mipmap’ов;
									  {GL_LINEAR_MIPMAP_LINEAR,  GL_LINEAR,				1},  // 4)Трилинейная фильтрация;
									  {GL_LINEAR_MIPMAP_LINEAR,  GL_LINEAR,				2},  // 5)Анизотропная фильтрация х2;
									  {GL_LINEAR_MIPMAP_LINEAR,  GL_LINEAR,				4},  // 6)Анизотропная фильтрация х4;
									  {GL_LINEAR_MIPMAP_LINEAR,  GL_LINEAR,				8},  // 7)Анизотропная фильтрация х8;
									  {GL_LINEAR_MIPMAP_LINEAR,  GL_LINEAR,				16}, // 8)Анизотропная фильтрация х16;
									  {GL_LINEAR_MIPMAP_LINEAR,  GL_LINEAR,				32}, // 9)Анизотропная фильтрация х32;
	};
	for (int i = 0; i < 3; i++)
		glTexParameteri(GL_TEXTURE_2D, filters[i], filterMode[mode][i]);
}