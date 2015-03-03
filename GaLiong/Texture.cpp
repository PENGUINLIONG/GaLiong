#include "Texture.h"

_L_BEGIN
Texture::Texture() : size({ 0, 0 })
{
}

Texture::~Texture()
{
	if (data && informative)
	{
		delete[] data;
	}
}

void Texture::ChangeFilter(Flag filter)
{
	glBindTexture(GL_TEXTURE_2D, index);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
}

SizeD Texture::CalculateDuplication(Size &container)
{
	Size _size = GetSize();
	return{ (double)container.Width / (double)(_size.Width),
		(double)container.Height / (double)(_size.Height) };
}

unsigned char Texture::GetPixelLength(Flag pixelFormat, Flag byteSize)
{
	if (byteSize == ByteSize::UByte)
	{
		switch (pixelFormat)
		{
			case PixelFormat::Alpha:
				return 1;
			case PixelFormat::RGBA:
			case PixelFormat::BGRA:
				return 4;
			case PixelFormat::RGB:
			case PixelFormat::BGR:
				return 3;
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

void Texture::Generate(Flag filter, TextureIndex index)
{
	lock_guard<recursive_mutex> lock(occupy);

	if (!size.Width || !size.Height || !data)
		return;

	if (index)
		this->index = index;
	else
		glGenTextures(1, &this->index);
	glBindTexture(GL_TEXTURE_2D, this->index);
	glPixelStorei(GL_UNPACK_ALIGNMENT, GetPixelLength());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLenum>(filter));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLenum>(filter));
	//gluBuild2DMipmapsIO_TEXTURE_2D, 3, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, data); // Before
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.Width, size.Height, 0, pixelFormat, byteSize, data); // After
}
_L_END