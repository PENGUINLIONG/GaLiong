#include "PNG.h"

_L_BEGIN
PNG::PNG()
{
	//                               IHDR        PLTE        IDAT        IEND
	const DWORD chunkTypeList[4] = { 0x52444849, 0x45547680, 0x54414449, 0x444E4549 };
}

void PNG::ToTexture(wchar_t *path, TextureBase &texture, FileReadOption option = FileReadOption::None)
{
	if (stream.is_open())
		stream.close();
	stream.open(path, stream.in | stream.binary | stream._Nocreate);
	Signature s = 0;
	stream.read((char *)s, 8);
	if (s != 0x0A1A0A0D474E5089)
		return;

}

PNG::~PNG()
{

}
_L_END