#pragma once
#include "Preprocess.h"
#include "Texture.h"
#include "TextureBuffer.h"
#include "BMP.h"

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
	static ImageFileFormat Detect(ifstream &stream, wchar_t * path)
	{
		ImageFileFormat &&format = _Detect(stream, path);
		stream.close();
		return format;
	}
	static bool AssertFormat(ifstream &stream, wchar_t * path, ImageFileFormat format)
	{
		return Detect(stream, path) == format;
	}
	static void DetectAndRead(ifstream &stream, wchar_t *path, Texture &target);
	static void DetectAndRead(ifstream &stream, wchar_t *path, TextureBuffer &target);
private:
	static ImageFileFormat _Detect(ifstream &stream, wchar_t * path);
};
_L_END