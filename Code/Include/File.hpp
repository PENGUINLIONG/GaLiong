#pragma once
#include "Preprocess.hpp"
#include "Texture.hpp"
#include "BMP.hpp"
/*
#include "PNG.hpp"
#include "WAV.hpp"
 */

_L_BEGIN
namespace IO
{
	enum class FileFormat
	{
		Bmp,
		/*
		PNG,
		WAV,
		 */
		Unsupported
	};

	class _L_ File
	{
	public:
		static bool Assert(wstring& path, FileFormat format);
		static FileFormat Detect(wstring& path);
	private:
		static FileFormat DoDetect(wchar_t *path);
	};
}
_L_END