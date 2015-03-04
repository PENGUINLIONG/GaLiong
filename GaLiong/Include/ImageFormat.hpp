#pragma once
#include "Preprocess.hpp"
#include "Texture.hpp"
#include "BMP.hpp"
#include "PNG.hpp"

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
	static TextureRef DetectAndRead(ifstream &stream, wchar_t *path);
private:
	static ImageFileFormat DoDetect(ifstream &stream, wchar_t *path);
};
_L_END