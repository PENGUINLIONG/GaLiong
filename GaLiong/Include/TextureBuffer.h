#pragma once
#include "Preprocess.h"
#include "Texture.h"
#include "TextureBase.h"

_L_BEGIN
class _L_ TextureBuffer : public TextureBase
{
public:
	TextureBuffer();
	TextureBuffer(unsigned char length);
	virtual Texture &Get() override final
	{
		return *current;
	}
	virtual void Set(unsigned long dataLength, unsigned char *data, Size size, WORD pixelFormat, WORD byteSize) override final
	{
		delete current;
		current = new Texture();
		current->Set(dataLength, data, size, pixelFormat, byteSize);
	}
	void Set(Texture *source)
	{
		current = source;
	}
	virtual const unsigned char *GetData() override final
	{
		return current->GetData();
	}
	virtual const Size GetSize() override final
	{
		return current->GetSize();
	}
	virtual const unsigned char GetPixelLength() override final
	{
		return current->GetPixelLength();
	}
	virtual const bool IsAvailable() override final
	{
		return current->IsAvailable();
	}
	virtual const bool IsInformative() override final
	{
		return current->IsInformative();
	}
	virtual const bool SameType(WORD pixelFormat, WORD byteSize) override final
	{
		return current->SameType(pixelFormat, byteSize);
	}
	TextureBuffer &MoveNext()
	{
		return MoveFor(1);
	}
	TextureBuffer &MoveFor(unsigned char steps);
	void Append(Texture *source);
	~TextureBuffer();
	friend void Append(Texture *source);
private:
	bool available = false;
	bool informative = false;
	unsigned char max = 0;
	Texture *textures = nullptr, *last = nullptr, *current = nullptr, *append = nullptr;
};
_L_END