#include "PNG.h"

_L_BEGIN
PNG::PNG()
{
	pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
	pngInfoPtr = png_create_info_struct(pngPtr);
	png_set_read_fn(pngPtr, &stream, ReadDataUsingFileStream);
}
PNG::~PNG()
{
	png_destroy_read_struct(&pngPtr, &pngInfoPtr, nullptr);
}

bool PNG::InitHeader(Size &size, TextureBase::PixelFormat &pixelFormat, TextureBase::ByteSize &byteSize)
{
	// Check the signature.
	Byte signature[8];
	stream.read(reinterpret_cast<char *>(signature), 8);
	if (png_sig_cmp(signature, 0, 7))
	{
		Log << L"PNG: Unexpected signature.";
		return false;
	}
	png_set_sig_bytes(pngPtr, 8);
	png_read_info(pngPtr, pngInfoPtr);
	Chunk_IHDR ihdr;
	png_get_IHDR(pngPtr, pngInfoPtr, &ihdr.Width, &ihdr.Height, &ihdr.BitDepth, &ihdr.ColorType, &ihdr.InterlaceMethod, &ihdr.CompressionMethod, &ihdr.FilterMethod);
	if (!ihdr.ColorType)
		goto failed;
	size = { ihdr.Width, ihdr.Height };

	// PixelFormat
	if (ihdr.ColorType & 0x01)
	{
		png_set_palette_to_rgb(pngPtr);
		pixelFormat = TextureBase::PixelFormat::RGB;
	}
	else
	{
		switch (ihdr.ColorType)
		{
			case 2:
				pixelFormat = TextureBase::PixelFormat::RGB;
				break;
			case 6:
				pixelFormat = TextureBase::PixelFormat::RGBA;
				break;
			default:
				goto failed;
		}
	}

	// ByteSize
	switch (ihdr.BitDepth)
	{
		case 8:
			byteSize = TextureBase::ByteSize::UByte;
			break;
		case 16:
			byteSize = TextureBase::ByteSize::UShort;
			break;
		default:
			goto failed;
	}

	return true;
failed:
	Log << L"Unsupported format";
	return false;
}

Buffer PNG::ReadData(const Size size, BufferLength &dataLength, const Byte pixelLength)
{
	BufferLength advance = size.Width * pixelLength;
	dataLength = advance * size.Height;
	Buffer data = new Byte[dataLength];
	Buffer *rowArray = new Buffer[size.Height];

	for (long i = 0; i < size.Height; i++)
	{
		long revRowIndex = (size.Height - i - 1) * advance;
		rowArray[i] = data + revRowIndex;
	}
	png_read_image(pngPtr, rowArray);
	delete [] rowArray;

	return data;
}

void PNG::ToTexture(wchar_t *path, TextureBase *texture, Flag option)
{
	Log << L"PNG: Try loading " << path << L"..." << EndLog;
	if (stream.is_open())
		stream.close();
	stream.open(path, stream.in | stream.binary | stream._Nocreate);
	
	Size size;
	TextureBase::PixelFormat pixelFormat;
	TextureBase::ByteSize byteSize;

	if (InitHeader(size, pixelFormat, byteSize))
	{
		BufferLength dataLength;
		Buffer data = ReadData(size, dataLength, Texture::GetPixelLength(pixelFormat, byteSize));

		texture->Set(dataLength, data, size, pixelFormat, byteSize);
		if ((option & FileReadOption::NoGenerate) == FileReadOption::None)
			texture->Generate();
	}
	else
	{
		Log.Log((L"PNG: Failed in loading " + wstring(path) + L"!").c_str(), Logger::WarningLevel::Warn);
		return;
	}
	
	if ((option & FileReadOption::NoClose) == FileReadOption::None)
		stream.close();
	Log << L"PNG: Succeeded." << EndLog;
}

void PNG::ReadDataUsingFileStream(png_structp pngPtr, png_bytep data, png_size_t length)
{
	(reinterpret_cast<ifstream *>(png_get_io_ptr(pngPtr)))->read(reinterpret_cast<char *>(data), length);
}
_L_END