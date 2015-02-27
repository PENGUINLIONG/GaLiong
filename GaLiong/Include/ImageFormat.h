#pragma once
#include "Preprocess.h"
#include "TextureBase.h"
#include "BMP.h"
#include "PNG.h"

_L_BEGIN
enum class ImageFileFormat
{
	BMP,
	JPEG,
	PNG,
	GIF,
	Undefined
};

class _L_ ImageFormat
{
public:
	static ImageFileFormat Detect(ifstream &stream, wchar_t *path);
	static bool Assert(ifstream &stream, wchar_t * path, ImageFileFormat format);
	static void DetectAndRead(ifstream &stream, wchar_t *path, TextureRef target);
private:
	static ImageFileFormat DoDetect(ifstream &stream, wchar_t *path);
};
_L_END