#pragma once
#include "Preprocess.h"
#include "Logger.h"
#include "TextureBase.h"

_L_BEGIN


class _L_ PNG
{
public:
	typedef struct
	{
		Byte4 Width;
		Byte4 Height;
		int BitDepth;
		int ColorType;
		int CompressionMethod;
		int FilterMethod;
		int InterlaceMethod;
	} Chunk_IHDR;

	PNG();
	~PNG();
	bool InitHeader(Size &size, TextureBase::PixelFormat &pixelFormat, TextureBase::ByteSize &byteSize);
	Buffer ReadData(const Size size, BufferLength &dataLength, const Byte pixelLength);
	void ToTexture(wchar_t *path, TextureBase *texture, FileReadOption option = FileReadOption::None);
#ifdef _INSIDER_COMPILATION
private:
	ifstream stream;
	png_structp pngPtr;
	png_infop pngInfoPtr;

	static void ReadDataUsingFileStream(png_structp pngPtr, png_bytep data, png_size_t length);
#endif
};
_L_END