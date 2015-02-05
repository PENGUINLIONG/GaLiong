#include "ImageFormat.h"

_L_BEGIN
ImageFileFormat ImageFormat::_Detect(ifstream &stream, wchar_t *path)
{
	stream.open(path, stream.in | stream.binary | stream._Nocreate);
	stream.seekg(stream.beg);

	DWORD32 tag = 0;
	stream.read((char *)&tag, 4);
	if ((tag & 0x0000FFFF) == 0x00004D42)
		return ImageFileFormat::BMP;
	switch (tag)
	{
	case 0xFFD8FFE0: return ImageFileFormat::JPEG;
	case 0x89504E47: return ImageFileFormat::PNG;
	case 0x47494638: return ImageFileFormat::GIF;
	default: return ImageFileFormat::Undefined;
	}
}

void ImageFormat::DetectAndRead(ifstream &stream, wchar_t *path, Texture &target)
{
	if (stream.is_open())
		stream.close();
	ImageFileFormat &&format = _Detect(stream, path);
	stream.seekg(stream.beg);
	switch (format)
	{
		case ImageFileFormat::BMP:
			BMP::Automatic_Unsafe(stream, path, target); break;
		//case ImageFileFormat::PNG:
			// ...
		default: break;
	}
	stream.close();
}
void ImageFormat::DetectAndRead(ifstream &stream, wchar_t *path, TextureBuffer &target)
{
	if (stream.is_open())
		stream.close();
	ImageFileFormat &&format = _Detect(stream, path);
	stream.seekg(stream.beg);
	switch (format)
	{
		case ImageFileFormat::BMP:
			BMP::Automatic_Unsafe(stream, path, *target.Current); break;
			//case ImageFileFormat::PNG:
			// ...
		default: break;
	}
	stream.close();
}
_L_END