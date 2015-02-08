 #include "BMP.h"

_L_BEGIN
bool BMP::InitHeader(ifstream &stream, Size &size, int &length)
{
	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;
	stream.read((char *)&bf, sizeof(BITMAPFILEHEADER));
	stream.read((char *)&bi, sizeof(BITMAPINFOHEADER));
	if (bi.biBitCount != 24)
		return false;
	size = { bi.biWidth, bi.biHeight };
	length = bi.biSizeImage ? bi.biSizeImage : bi.biWidth * bi.biHeight * 3;

	stream.seekg(bf.bfOffBits, stream.beg);
	return true;
}

unsigned char *BMP::ReadData(ifstream &stream, int length)
{
	unsigned char *data = new unsigned char[length]; // NEED TO BE DELETED.
	stream.read((char *)data, length);

	return data;
}

void BMP::Automatic(ifstream &stream, wchar_t *path, Texture &texture)
{
	if (stream.is_open())
		stream.close();
	stream.open(path, stream.in | stream.binary | stream._Nocreate);
	Automatic_Unsafe(stream, path, texture);
	stream.close();
}
void BMP::Automatic(ifstream &stream, wchar_t *path, TextureBuffer &texture)
{
	Automatic(stream, path, texture.GetCurrent());
}

void BMP::Automatic_Unsafe(ifstream &stream, wchar_t *path, Texture &texture)
{
	if (InitHeader(stream, texture.Size, texture.DataLength))
	{
		unsigned char *data = ReadData(stream, texture.DataLength);
#ifdef _DEBUG
		texture.Path = path;
#endif
		texture.Data = data;
		texture.PixelFormat = GL_BGR_EXT;
		texture.ByteSize = GL_UNSIGNED_BYTE;
		texture.Generate();
		texture.Informative = true;
	}
}
_L_END