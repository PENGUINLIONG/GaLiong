#pragma once
#include "Preprocess.h"
#include "Texture.h"

_L_BEGIN
class _L_ TextureBuffer
{
public:
	TextureBuffer();
	TextureBuffer(unsigned char length);
	inline Texture &GetCurrent()
	{
		return *current;
	}
	inline void SetCurrent(Texture *source)
	{
		current = source;
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
	bool available = false;
	unsigned char max = 0;
	Texture *textures = nullptr, *last = nullptr, *current = nullptr, *append = nullptr;

};
_L_END