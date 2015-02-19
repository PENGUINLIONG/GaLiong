#pragma once
#include "Preprocess.h"
#include "TextureBase.h"

_L_BEGIN
class _L_ Texture : public TextureBase
{
public:
	Texture();
	static unsigned char GetPixelLength(PixelFormat pixelFormat, ByteSize byteSize);
	virtual Texture &Get() override final
	{
		return *this;
	}
	virtual const bool IsAvailable() override final
	{
		return available;
	}
	virtual const bool IsInformative() override final
	{
		return informative;
	}
	virtual void Generate()
	{
		Generate(Filter::Linear);
	}
	void Generate(Filter filter);
	virtual const unsigned char *GetData() override final
	{
		return data;
	}
	virtual const TextureID GetIndex() override final
	{
		return index;
	}
	virtual const Size GetSize() override final
	{
		return size;
	}
	virtual const unsigned char GetPixelLength() override final
	{
		return informative ? GetPixelLength(pixelFormat, byteSize) : 0;
	}
	virtual const bool SameType(PixelFormat pixelFormat, ByteSize byteSize) override final
	{
		return (this->pixelFormat == pixelFormat && this->byteSize == byteSize);
	}
	virtual void Set(unsigned long dataLength, unsigned char *data, Size size, PixelFormat pixelFormat, ByteSize byteSize) override final
	{
		if (this->data)
			delete this->data;
		this->dataLength = dataLength;
		this->data = data;
		this->size = size;
		this->pixelFormat = pixelFormat;
		this->byteSize = byteSize;
		if (data)
			informative = true;
		available = true;
	}
	~Texture();
private:
	bool available = false;
	bool informative = false;
	unsigned long dataLength = 0;
	unsigned char *data = nullptr;
	TextureID index = 0;
	Size size;
	PixelFormat pixelFormat;
	ByteSize byteSize;
};

typedef struct
{
	Rect Rect;
	Texture *Texture;
} TextureConponent;
_L_END
