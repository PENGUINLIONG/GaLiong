#pragma once
#include "Preprocess.hpp"
#include "Logger.hpp"
#include "Texture.hpp"
#include "TextureManager.hpp"

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
	Buffer ReadData(const Size &size, BufferLength &dataLength, const Byte pixelLength);
	TextureRef ToTexture(wchar_t *path, Flag option = FileReadOption::None);
#ifdef _INSIDER_COMPILATION
private:
	ifstream stream;
	png_structp pngPtr;
	png_infop pngInfoPtr;

	static void ReadDataUsingFileStream(png_structp pngPtr, png_bytep data, png_size_t length);
#endif
};
_L_END