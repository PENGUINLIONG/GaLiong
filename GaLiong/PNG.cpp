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
	png_destroy_info_struct(pngPtr, &pngInfoPtr);
	png_destroy_read_struct(&pngPtr, &pngInfoPtr, &pngInfoPtr);
}

bool PNG::InitHeader(Size &size, BufferLength &length, TextureBase::PixelFormat &pixelFormat, TextureBase::ByteSize &byteSize)
{
	// Check the signature.
	Byte signature[8];
	stream.read(reinterpret_cast<char *>(signature), 8);
	if (png_sig_cmp(signature, 0, 7))
		return false;
	png_set_sig_bytes(pngPtr, 8);
	png_read_info(pngPtr, pngInfoPtr);
	png_get_IHDR(pngPtr, pngInfoPtr, &_width, &_height, &bit_depth, &color_type, &interlace_type, &compression_type, &filter_method);
	size = { png_get_image_width(pngPtr, pngInfoPtr), png_get_image_width(pngPtr, pngInfoPtr) };
	// PixelFormat
	if (png_get_color_type(pngPtr, pngInfoPtr) & 0x01)
	{
		Log << L"U"
	}
	switch (png_get_color_type(pngPtr, pngInfoPtr))
	{
		case :
			break;
		case :
			break;
	}
	// ByteSize
	switch (png_get_bit_depth(pngPtr, pngInfoPtr))
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

Buffer ReadChunk(BufferLength length)
{

}

void PNG::ToTexture(wchar_t *path, TextureBase *texture, FileReadOption option)
{
	Log << L"PNG: Try loading " << path << L"...";
	if (stream.is_open())
		stream.close();
	stream.open(path, stream.in | stream.binary | stream._Nocreate);
	
	Size size;
	BufferLength dataLength;
	TextureBase::PixelFormat pixelFormat;
	TextureBase::ByteSize byteSize;

	if (!InitHeader())
	{
		Log.Log(L"PNG: Unexpected signature.", Logger::WarningLevel::Warn);
		return;
	}



	Log << L"PNG: Succeeded.";
}

void ReadDataUsingFileStream(png_structp pngPtr, png_bytep data, png_size_t length)
{
	(reinterpret_cast<ifstream *>(png_get_io_ptr(pngPtr)))->read(reinterpret_cast<char *>(data), length);
}
_L_END