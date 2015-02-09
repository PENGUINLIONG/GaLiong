#pragma once
#include "Preprocess.h"
#include "Texture.h"
#include "ITexture.h"

_L_BEGIN
class _L_ TextureBuffer : public ITexture
{
public:
	TextureBuffer();
	TextureBuffer(unsigned char length);
	virtual inline Texture &Get() override final
	{
		return *current;
	}
	virtual inline void Set(unsigned long dataLength, unsigned char *data, Size size, WORD pixelFormat, WORD byteSize) override final
	{
		delete current;
		current = new Texture();
		current->Set(dataLength, data, size, pixelFormat, byteSize);
	}
	inline void Set(Texture *source)
	{
		current = source;
	}
	virtual inline const unsigned char *GetData() override final
	{
		return current->GetData();
	}
	virtual inline const Size GetSize() override final
	{
		return current->GetSize();
	}
	virtual inline const unsigned char GetPixelLength() override final
	{
		return current->GetPixelLength();
	}
	virtual inline const bool IsAvailable() override final
	{
		return current->IsAvailable();
	}
	virtual inline const bool IsInformative() override final
	{
		return current->IsInformative();
	}
	virtual inline const bool SameType(WORD pixelFormat, WORD byteSize) override final
	{
		return current->SameType(pixelFormat, byteSize);
	}
	inline TextureBuffer &MoveNext()
	{
		return MoveFor(1);
	}
	TextureBuffer &MoveFor(unsigned char steps);
	void Append(Texture *source);
	~TextureBuffer();
	friend void TextureBuffer::Append(Texture *source);
private:
	unsigned char max = 0;
	Texture *textures = nullptr, *last = nullptr, *current = nullptr, *append = nullptr;
};
_L_END