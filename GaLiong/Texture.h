#pragma once
#include "Preprocess.h"
#include "ITexture.h"

_L_BEGIN
class _L_ Texture : public ITexture
{
public:
	Texture();
	static unsigned char GetPixelLength(WORD pixelFormat, WORD byteSize);
	virtual inline Texture &Get() override final
	{
		return *this;
	}
	virtual inline void Set(unsigned long dataLength, unsigned char *data, Size size, WORD pixelFormat, WORD byteSize) override final
	{
		this->dataLength = dataLength;
		this->data = data;
		this->size = size;
		this->pixelFormat = pixelFormat;
		this->byteSize = byteSize;
		if (data)
			informative = true;
		available = true;
	}
	virtual inline const unsigned char *GetData() override final
	{
		return data;
	}
	virtual inline const Size GetSize() override final
	{
		return size;
	}
	virtual inline const unsigned char GetPixelLength() override final
	{
		return available ? GetPixelLength(pixelFormat, byteSize) : 0;
	}
	virtual inline const bool IsAvailable() override final
	{
		return available;
	}
	virtual inline const bool IsInformative() override final
	{
		return informative;
	}
	virtual inline const bool SameType(WORD pixelFormat, WORD byteSize) override final
	{
		return this->pixelFormat == pixelFormat && this->byteSize == byteSize;
	}
	inline const GLuint GetIndex()
	{
		return index;
	}
	void Generate();
	~Texture();
private:
	unsigned long dataLength = 0;
	unsigned char *data = nullptr;
	GLuint index = 0;
	Size size;
	WORD pixelFormat, byteSize;
};

typedef struct
{
	Rect Rect;
	Texture *Texture;
} TextureConponent;
_L_END