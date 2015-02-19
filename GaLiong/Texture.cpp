#include "Texture.h"

_L_BEGIN
Texture::Texture() : size({ 0, 0 })
{
}

unsigned char Texture::GetPixelLength(PixelFormat pixelFormat, ByteSize byteSize)
{
	if (byteSize == ByteSize::UByte)
	{
		switch (pixelFormat)
		{
			case PixelFormat::Alpha:
				return 1;
			case PixelFormat::BGR:
			case PixelFormat::RGB:
				return 3;
			case PixelFormat::RGBA:
			case PixelFormat::BGRA:
				return 4;
			default: break;
		}
	}
	else if (byteSize == ByteSize::UShort)
	{
		switch (pixelFormat)
		{
			case PixelFormat::RGB:
				return 6;
			case PixelFormat::RGBA:
				return 8;
			case PixelFormat::Alpha:
				return 2;
			default: break;
		}
	}
	return 0;
}

void Texture::Generate(Filter filter)
{
	if (!size.Width || !size.Height || !data)
		return;
	TextureID textureIndex;

	glGenTextures(1, &textureIndex);
	glBindTexture(GL_TEXTURE_2D, textureIndex);
	glPixelStorei(GL_UNPACK_ALIGNMENT, GetPixelLength());
	//gluBuild2DMipmapsIO_TEXTURE_2D, 3, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, data); // Before
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.Width, size.Height, 0, static_cast<GLenum>(pixelFormat), static_cast<GLenum>(byteSize), data); // After
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLenum>(filter));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLenum>(filter));
	index = textureIndex;
	available = true;
}

Texture::~Texture()
{
	if (data && available)
	{
		delete[] data;
		data = nullptr;
		available = false;
	}
}
_L_END