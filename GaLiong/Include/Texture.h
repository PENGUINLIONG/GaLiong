#pragma once
#include "Preprocess.h"
#include "TextureBase.h"

_L_BEGIN
class _L_ Texture : public TextureBase
{
public:
	Texture();
	static unsigned char GetPixelLength(WORD pixelFormat, WORD byteSize);
	virtual Texture &Get() override final
	{
		return *this;
	}
	virtual void Set(unsigned long dataLength, unsigned char *data, Size size, WORD pixelFormat, WORD byteSize) override final
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
	virtual const unsigned char *GetData() override final
	{
		return data;
	}
	virtual const Size GetSize() override final
	{
		return size;
	}
	virtual const unsigned char GetPixelLength() override final
	{
		return informative ? GetPixelLength(pixelFormat, byteSize) : 0;
	}
	virtual const bool IsAvailable() override final
	{
		return available;
	}
	virtual const bool IsInformative() override final
	{
		return informative;
	}
	virtual const bool SameType(WORD pixelFormat, WORD byteSize) override final
	{
		return (this->pixelFormat == pixelFormat && this->byteSize == byteSize);
	}
	const GLuint GetIndex()
	{
		return index;
	}
	void Generate()
	{
		Generate(GL_LINEAR);
	}
	void Generate(WORD filter);
	~Texture();
private:
	bool available = false;
	bool informative = false;
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