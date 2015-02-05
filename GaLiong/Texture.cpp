#include "Texture.h"

_L_BEGIN
Texture::Texture()
{
}

int Texture::GetPixelLength(WORD pixelFormat, WORD byteSize)
{
	if (byteSize == GL_UNSIGNED_BYTE)
	{
		switch (pixelFormat)
		{
			case GL_ALPHA:
				return 1;
			case GL_BGR_EXT:
			case GL_RGB:
				return 3;
			case GL_RGBA:
			case GL_BGRA_EXT:
				return 4;
			default: break;
		}
	}
	else if (byteSize == GL_UNSIGNED_SHORT)
	{
		switch (pixelFormat)
		{
			case GL_RGB:
				return 6;
			case GL_RGBA:
				return 8;
			case GL_ALPHA:
				return 2;
			default: break;
		}
	}
	return 0;
}
int Texture::GetPixelLength()
{
	return	available ? GetPixelLength(PixelFormat, ByteSize) : 0;
}

void Texture::Generate()
{
	if (!PixelFormat || !Size.Width || !Size.Height || !PixelFormat || !ByteSize || !Data)
		return;
	GLuint textureIndex;

	glGenTextures(1, &textureIndex);
	glBindTexture(GL_TEXTURE_2D, textureIndex);
	glPixelStorei(GL_UNPACK_ALIGNMENT, GetPixelLength());
	//gluBuild2DMipmapsIO_TEXTURE_2D, 3, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, data); // Before
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Size.Width, Size.Height, 0, PixelFormat, ByteSize, Data); // After
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Index = textureIndex;
	available = true;
}

Texture::~Texture()
{
	if (Data && available)
	{
		delete[] Data;
		Data = nullptr;
		available = false;
	}
}
_L_END