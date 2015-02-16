#pragma once
#include "Preprocess.h"
#include "TextureBase.h"

_L_BEGIN
class _L_ BMP
{
public:
	typedef struct
	{
		WORD Type;
		DWORD32 Size;
		WORD Reserved1;
		WORD Reserved2;
		DWORD32 OffBits;
	} FileHeader;
	typedef struct
	{
		DWORD32 Size;
		LONG Width;
		LONG Height;
		WORD Planes;
		WORD BitCount;
		DWORD32 Compression;
		DWORD32 SizeImage;
		LONG XPelsPerMeter;
		LONG YPelsPerMeter;
		DWORD32 ClrUsed;
		DWORD32 ClrImportant;
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
