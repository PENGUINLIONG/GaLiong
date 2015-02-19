#include "ImageFormat.h"

_L_BEGIN
bool ImageFormat::Assert(ifstream &stream, wchar_t * path, ImageFileFormat format)
{
	return Detect(stream, path) == format;
}

ImageFileFormat ImageFormat::Detect(ifstream &stream, wchar_t * path)
{
	ImageFileFormat &&format = DoDetect(stream, path);
	stream.close();
	return format;
}

void ImageFormat::DetectAndRead(ifstream &stream, wchar_t *path, TextureBase *target)
{
	if (stream.is_open())
		stream.close();
	ImageFileFormat &&format = DoDetect(stream, path);
	stream.close();

	switch (format)
	{
		case ImageFileFormat::BMP:
		{
			BMP bmp;
			bmp.ToTexture(path, target);
			break;
		}
		case ImageFileFormat::PNG:
			// ... 
			break;
		default: break;
	}
}

ImageFileFormat ImageFormat::DoDetect(ifstream &stream, wchar_t *path)
{
	stream.open(path, stream.in | stream.binary | stream._Nocreate);

	Byte4 tag = 0;
	stream.read((char *)&tag, 4);
	if ((tag & 0x0000FFFF) == 0x00004D42)
		return ImageFileFormat::BMP;
	switch (tag)
	{
		case 0xFFD8FFE0:
			return ImageFileFormat::JPEG;
		case 0x474E5089:
			if (stream.read((char *)&tag, 4))
			return tag == 0x0A1A0A0D ? ImageFileFormat::PNG : ImageFileFormat::Undefined;
		case 0x47494638: return ImageFileFormat::GIF;
		default:
			return ImageFileFormat::Undefined;
	}
}
_L_END