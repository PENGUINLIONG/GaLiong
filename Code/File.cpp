#include "File.hpp"

_L_BEGIN
namespace IO
{
	bool File::Assert(wstring& path, FileFormat format)
	{
		return Detect(path) == format;
	}

	FileFormat File::Detect(wstring& path)
	{
		stream.open(path, stream.in | stream.binary | stream._Nocreate);
		
		Byte4 tag = 0;
		stream.read((char *)&tag, 4);
		if ((tag & 0x0000FFFF) == 0x00004D42)
			return FileFormat::BMP;
		
		FileFormat format;
		
		switch (tag)
		{
			case 0x474E5089:
				stream.read((char *)&tag, 4);
				if (tag == 0x0A1A0A0D)
					return FileFormat::PNG;
				return FileFormat::Undefined;
			case 0x46464952:
				stream.read((char *)&tag, 4);
				if (tag == 0x45564157)
					return FileFormat::WAV;
				format = FileFormat::Undefined;
				break;
			default:
				format = FileFormat::Undefined;
				break;
		}
		
		stream.close();
		return format;
	}

	TextureRef FileImpl::Read(wchar_t *path)
	{
		if (stream.is_open())
			stream.close();
		FileFormat &&format = DoDetect(path);
		stream.close();

		switch (format)
		{
			case FileFormat::BMP:
			{
				BMP bmp;
				return bmp.ToTexture(path);
			}
			case FileFormat::PNG:
			{
				PNG png;
				return png.ToTexture(path);
			}
			default:
				return TextureRef();
		}
	}
}
_L_END