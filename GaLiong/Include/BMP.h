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
		DWORD Size;
		WORD Reserved1;
		WORD Reserved2;
		DWORD OffBits;
	} FileHeader;
	typedef struct
	{
		DWORD Size;
		LONG Width;
		LONG Height;
		WORD Planes;
		WORD BitCount;
		DWORD Compression;
		DWORD SizeImage;
		LONG XPelsPerMeter;
		LONG YPelsPerMeter;
		DWORD ClrUsed;
		DWORD ClrImportant;
	} InfoHeader;

	BMP();
	bool InitHeader(Size &size, unsigned long &length);
	unsigned char *ReadData(unsigned long length);
	void ToTexture(wchar_t *path, TextureBase &texture, FileReadOption option = FileReadOption::None);
	void Automatic_Unsafe(wchar_t *path, TextureBase &texture);
	~BMP();
private:
	ifstream stream;
};
_L_END
