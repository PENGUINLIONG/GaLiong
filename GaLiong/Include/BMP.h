#pragma once
#include "Preprocess.h"
#include "TextureBase.h"

_L_BEGIN
class _L_ BMP
{
public:
	typedef struct
	{
		Byte2 Type;
		Byte4 Size;
		Byte2 Reserved1;
		Byte2 Reserved2;
		Byte4 OffBits;
	} FileHeader;
	typedef struct
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
	} InfoHeader;

	BMP();
	bool InitHeader(Size &size, unsigned long &length);
	unsigned char *ReadData(unsigned long length);
	void ToTexture(wchar_t *path, TextureBase *texture, FileReadOption option = FileReadOption::None);
	~BMP();
private:
	ifstream stream;
};
_L_END
