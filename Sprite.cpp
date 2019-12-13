#include "Sprite.h"

Sprite::Sprite() :height(0), width(0), spriteBufferId(0)
{
}

Sprite::Sprite(std::string filename)
{
	load(filename);
}

void Sprite::load(std::string filename)
{
	// создаем новое "изображение"
	ILuint imageId = ilGenImage();
	// задаем текущее "изображение"
	ilBindImage(imageId);
	// загружаем изображение
	bool result = ilLoadImage(filename.c_str());
	// получение параметров загруженной текстуры
	int width = ilGetInteger(IL_IMAGE_WIDTH);
	int  height = ilGetInteger(IL_IMAGE_HEIGHT);
	int  format = ilGetInteger(IL_IMAGE_FORMAT);
	int  type = ilGetInteger(IL_IMAGE_TYPE);

	printf("Filename is %s\n", filename);
	printf("Width - %d, Height - %i, format - %d, type - %d\n", width, height, format, type);
	switch (format)
	{
	case IL_RGB:
		printf("Format is RGB\n");
		break;
	case IL_RGBA:
		printf("Format is RGBA\n");
		break;
	case IL_BGR:
		printf("Format is BGR\n");
		break;
	case IL_BGRA:
		printf("Format is BGRA\n");
		break;
	case IL_COLOUR_INDEX:
		printf("Format is IL_COLOUR_INDEX\n");
		break;
	case IL_LUMINANCE:
		printf("Format is IL_LUMINANCE\n");
		break;
	default:
		printf("Unrecognized format\n");
		break;
	}
	switch (type)
	{
	case IL_BYTE:
		printf("Type is Byte\n");
		break;
	case IL_UNSIGNED_BYTE:
		printf("Type is unsigned byte\n");
		break;
	case IL_SHORT:
		printf("Type is short\n");
		break;
	case IL_UNSIGNED_SHORT:
		printf("Type is unsigned short\n");
		break;
	case IL_INT:
		printf("Type is int\n");
		break;
	case IL_UNSIGNED_INT:
		printf("Type is unsigned int\n");
		break;
	case IL_FLOAT:
		printf("Type is float\n");
		break;
	case IL_DOUBLE:
		printf("Type is double\n");
		break;
	default:
		printf("Unrecognized type\n");
		break;
	}

	ILinfo ImageInfo;
	iluGetImageInfo(&ImageInfo);
	if (ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
	{
		iluFlipImage();
	}

	GLubyte* RGBAsprite = new GLubyte[width * height * 4];
	ilCopyPixels(0, 0, 0, width, height, 1, IL_RGBA, GL_UNSIGNED_BYTE, RGBAsprite);

	spriteBufferId = 0;
	glGenBuffers(1, &spriteBufferId);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, spriteBufferId);
	glBufferData(GL_PIXEL_UNPACK_BUFFER, width * height * 4, RGBAsprite, GL_STATIC_DRAW);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
	
	this->width = width;
	this->height = height;

	ilDeleteImage(imageId);
}

void Sprite::draw(int x, int y)
{
	glDrawBuffer(GL_BACK);

	glWindowPos2i(x, y);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, spriteBufferId);
	glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
}

unsigned int Sprite::GetWidth()
{
	return width;
}

unsigned int Sprite::GetHeight()
{
	return height;
}
