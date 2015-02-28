#pragma once
#include "Preprocess.h"
#include "Logger.h"
#include "Texture.h"

_L_BEGIN
class _L_ PNG
{
public:
	struct Chunk_IHDR
	{
		Byte4 Width;
		Byte4 Height;
		int BitDepth;
		int ColorType;
		int CompressionMethod;
		int FilterMethod;
		int InterlaceMethod;
	};

	PNG();
	~PNG();
	bool InitHeader(Size &size, Flag &pixelFormat, Flag &byteSize);
	Buffer ReadData(const Size size, BufferLength &dataLength, const Byte pixelLength);
	void ToTexture(wchar_t *path, TextureRef texture, Flag option = FileReadOption::None);
#ifdef _INSIDER_COMPILATION
private:
	ifstream stream;
	png_structp pngPtr;
	png_infop pngInfoPtr;

	static void ReadDataUsingFileStream(png_structp pngPtr, png_bytep data, png_size_t length);
#endif
};
_L_END