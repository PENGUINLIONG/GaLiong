#include "Texture.h"

_L_BEGIN
Texture::Texture() : size({ 0, 0 })
{
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

void Texture::ChangeFilter(Flag filter)
{
	glBindTexture(GL_TEXTURE_2D, index);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
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

void Texture::Generate(Flag filter)
{
	if (!size.Width || !size.Height || !data)
		return;

	glGenTextures(1, &index);
	glBindTexture(GL_TEXTURE_2D, index);
	glPixelStorei(GL_UNPACK_ALIGNMENT, GetPixelLength());
	//gluBuild2DMipmapsIO_TEXTURE_2D, 3, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, data); // Before
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.Width, size.Height, 0, pixelFormat, byteSize, data); // After
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLenum>(filter));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLenum>(filter));
}

TextureRef TextureManager::NewTexture()
{
	TextureStrongRef ref(new Texture);
	refs.push_back(ref);
	return TextureRef(ref);
}

template<unsigned long TSize>
array<TextureRef, TSize> TextureManager::NewTextureArray()
{
	if (!TSize)
		return;
	array<TextureStrongRef, TSize> arr;
	array<TextureRef, TSize> rtn;
	long size = 0;
	for (TextureStrongRef ref : arr)
	{
		refs.push_back(ref);
		rtn[size] = TextureRef(ref);
		size++;
	}
	return rtn;
}
_L_END