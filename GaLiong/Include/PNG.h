#pragma once
#include "Preprocess.h"
#include "Logger.h"
#include "TextureBase.h"

_L_BEGIN
class _L_ PNG
{
public:
	PNG();
	~PNG();
	bool InitHeader(Size &size, BufferLength &length, TextureBase::PixelFormat &pixelFormat,TextureBase::ByteSize &byteSize);
	Buffer ReadChunk(BufferLength length);
	void ToTexture(wchar_t *path, TextureBase *texture, FileReadOption option = FileReadOption::None);
private:
#ifdef _INSIDER_COMPILATION
	ifstream stream;
	png_structp pngHandle;
	png_infop pngInfo;

	static void ReadDataUsingFileStream(png_structp pngPtr, png_bytep data, png_size_t length);
#endif
};
_L_END