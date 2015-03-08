#pragma once
#include "Preprocess.hpp"
#include "Texture.hpp"
#include "BMP.hpp"
#include "PNG.hpp"
#include "WAV.hpp"

_L_BEGIN
enum class FileFormat
{
	BMP,
	PNG,
	WAV,
	Undefined
};

class _L_ FileImpl
{
public:
	bool Assert(wchar_t * path, FileFormat format);
	FileFormat Detect(wchar_t *path);
	TextureRef Read(wchar_t *path);
private:
	FileFormat DoDetect(wchar_t *path);
	ifstream stream;
};

static FileImpl File;
_L_END