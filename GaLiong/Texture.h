#pragma once
#include "Preprocess.h"

_L_BEGIN
class _L_ Texture
{
public:
	bool Informative = false;
	int DataLength = 0;
	unsigned char *Data = nullptr;
	GLuint Index = 0;
	Size Size;
	WORD PixelFormat, ByteSize;
#ifdef _DEBUG
	wchar_t *Path = nullptr;
#endif

	Texture();
	static int GetPixelLength(WORD pixelFormat, WORD byteSize);
	int GetPixelLength();
	bool GetAvailability()
	{
		return available;
	}
	void Generate();
	~Texture();
private:
	bool available = false;
};

typedef struct
{
	Rect Rect;
	Texture *Texture;
} TextureConponent;
_L_END