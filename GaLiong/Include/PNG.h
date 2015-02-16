#pragma once
#include "Preprocess.h"
#include "TextureBase.h"

_L_BEGIN
struct PNGFileHeader
{
	DWORDLONG Signature;

};

class _L_ PNG
{
public:
	PNG();
	bool InitHeader(Size &size, unsigned long &length);
	unsigned char *ReadData(unsigned long length);
	void ToTexture(wchar_t *path, TextureBase &texture, FileReadOption option = FileReadOption::None);
	void Automatic_Unsafe(wchar_t *path, TextureBase &texture);
	~PNG();
private:
	ifstream stream;
};
_L_END