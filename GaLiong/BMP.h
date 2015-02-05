#pragma once
#include "Preprocess.h"
#include "Texture.h"
#include "TextureBuffer.h"

_L_BEGIN
class _L_ BMP
{
public:
	static bool InitHeader(ifstream &stream, Size &size, int &length);
	static unsigned char *ReadData(ifstream &stream, int length);
	static void Automatic(ifstream &stream, wchar_t *path, Texture &texture);
	static void Automatic(ifstream &stream, wchar_t *path, TextureBuffer &texture);
	static void Automatic_Unsafe(ifstream &stream, wchar_t *path, Texture &texture);
};
_L_END
