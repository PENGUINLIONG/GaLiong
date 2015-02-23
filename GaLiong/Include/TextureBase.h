#pragma once
#include "Preprocess.h"

_L_BEGIN
class Texture;

class _L_ TextureBase
{
public:
	enum class Filter : Flag
	{
		Nearest = 0x2600,
		Linear = 0x2601
	};
	enum class PixelFormat : Flag
	{
		Alpha = 0x1906,
		RGB = 0x1907,
		RGBA = 0x1908,
		BGR = 0x80E0,
		BGRA = 0x80E1
	};
	enum class ByteSize : Flag
	{
		UByte = 0x1401,
		UShort = 0x1403
	};
	virtual const bool IsAvailable() = 0;
	virtual const bool IsInformative() = 0;
	virtual void Generate() = 0;
	virtual Texture &Get() = 0;
	virtual const Buffer GetData() = 0;
	virtual const TextureID GetIndex() = 0;
	virtual const unsigned char GetPixelLength() = 0;
	virtual const Size GetSize() = 0;
	virtual const bool SameType(PixelFormat pixelFormat, ByteSize byteSize) = 0;
	virtual void Set(BufferLength dataLength, Buffer data, Size size, PixelFormat pixelFormat, ByteSize byteSize) = 0;
};
_L_END