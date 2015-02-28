#pragma once
#include "Preprocess.h"
#include "Texture.h"

_L_BEGIN
class _L_ Texture
{
public:
	const static struct Filter
	{
		const static Flag Nearest = 0x2600;
		const static Flag Linear = 0x2601;
	};
	const static struct PixelFormat
	{
		const static Flag Alpha = 0x1906;
		const static Flag RGB = 0x1907;
		const static Flag RGBA = 0x1908;
		const static Flag BGR = 0x80E0;
		const static Flag BGRA = 0x80E1;
	};
	const static struct ByteSize
	{
		const static Flag UByte = 0x1401;
		const static Flag UShort = 0x1403;
	};
	Texture();
	void ChangeFilter(Flag filter);
	static unsigned char GetPixelLength(Flag pixelFormat, Flag byteSize);
	void Generate(Flag filter = Filter::Linear);
	const Buffer GetData()
	{
		return data;
	}
	const TextureIndex GetIndex()
	{
		return index;
	}
	const Size GetSize()
	{
		return size;
	}
	const unsigned char GetPixelLength()
	{
		return informative ? GetPixelLength(pixelFormat, byteSize) : 0;
	}
	const bool SameType(Flag pixelFormat, Flag byteSize)
	{
		return (this->pixelFormat == pixelFormat && this->byteSize == byteSize);
	}
	void Set(BufferLength dataLength, Buffer data, Size size, Flag pixelFormat, Flag byteSize)
	{
		if (this->data)
			delete this->data;
		else return;
		this->dataLength = dataLength;
		this->data = data;
		this->size = size;
		this->pixelFormat = pixelFormat;
		this->byteSize = byteSize;
		informative = true;
	}
	~Texture();
private:
	bool informative = false;
	BufferLength dataLength = 0;
	Buffer data = nullptr;
	TextureIndex index = 0;
	Size size;
	Flag pixelFormat, byteSize;
};

typedef shared_ptr<Texture> TextureStrongRef;
typedef weak_ptr<Texture> TextureRef;
struct TextureComponent
{
	Rect Rect;
	TextureRef Texture;
};

class _L_ TextureManager
{
	static TextureRef NewTexture();
	template<unsigned long TSize>
	static array<TextureRef, TSize> NewTextureArray();
	static list<TextureStrongRef> refs;
};
_L_END