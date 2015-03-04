#pragma once
#include "Preprocess.hpp"
#include "Logger.hpp"
#include "Texture.hpp"
#include "TextureManager.hpp"

_L_BEGIN
class _L_ BMP
{
public:
	struct FileHeader
	{
		Byte2 Type;
		Byte4 Size;
		Byte2 Reserved1;
		Byte2 Reserved2;
		Byte4 OffBits;
	};
	struct InfoHeader
	{
		Byte4 Size;
		long Width;
		long Height;
		Byte2 Planes;
		Byte2 BitCount;
		Byte4 Compression;
		Byte4 SizeImage;
		long XPelsPerMeter;
		long YPelsPerMeter;
		Byte4 ClrUsed;
		Byte4 ClrImportant;
	};

	BMP();
	~BMP();
	bool InitHeader(Size &size, BufferLength &length);
	Buffer ReadData(BufferLength length);
	TextureRef ToTexture(wchar_t *path, Flag option = FileReadOption::None);
private:
	ifstream stream;
};
_L_END