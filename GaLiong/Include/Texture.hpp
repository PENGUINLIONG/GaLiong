#pragma once
#include "Preprocess.hpp"
#include "Texture.hpp"

_L_BEGIN
class _L_ Texture
{
public:
	recursive_mutex occupy;
	
	struct Filter
	{
		const static Flag Nearest = 0x2600;
		const static Flag Linear = 0x2601;
	};
	struct PixelFormat
	{
		const static Flag Ignore = 0x0000;
		const static Flag Alpha = 0x1906;
		const static Flag RGB = 0x1907;
		const static Flag RGBA = 0x1908;
		const static Flag BGR = 0x80E0;
		const static Flag BGRA = 0x80E1;
	};
	struct ByteSize
	{
		const static Flag Ignore = 0x0000;
		const static Flag UByte = 0x1401;
		const static Flag UShort = 0x1403;
	};

	Texture();
	~Texture();
	void ChangeFilter(Flag filter);
	SizeD CalculateDuplication(Size &container);
	static unsigned char GetPixelLength(Flag pixelFormat, Flag byteSize);
	void Generate(Flag filter = Filter::Linear, TextureIndex index = 0);
	const Buffer GetData()
	{
		return data;
	}
	const BufferLength GetDataLength()
	{
		return dataLength;
	}
	const TextureIndex GetIndex()
	{
		return index;
	}
	const Size GetSize()
	{
		return size;
	}
	const Byte GetPixelLength()
	{
		return informative ? GetPixelLength(pixelFormat, byteSize) : 0;
	}
	const bool IsInformative()
	{
		return informative;
	}
	const bool SameType(Flag pixelFormat, Flag byteSize = ByteSize::UByte)
	{
		return (!pixelFormat || !byteSize) ?
			(this->pixelFormat == pixelFormat || this->byteSize == byteSize) :
			(this->pixelFormat == pixelFormat && this->byteSize == byteSize);
	}
	void Set(BufferLength dataLength, Buffer data, Size size, Flag pixelFormat, Flag byteSize)
	{
		if (!data)
			return;
		if (this->data)
			delete this->data;
		if (dataLength >= size.Width * size.Height * GetPixelLength(pixelFormat, byteSize))
			this->dataLength = dataLength;
		this->data = data;
		this->size = size;
		this->pixelFormat = pixelFormat;
		this->byteSize = byteSize;
		informative = true;
	}
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
	Texture *Texture;
};
_L_END