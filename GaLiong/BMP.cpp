 #include "BMP.h"

_L_BEGIN
BMP::BMP() {}
BMP::~BMP() {}

bool BMP::InitHeader(Size &size, unsigned long &length)
{
	FileHeader f;
	InfoHeader i;
	stream.read((char *)&f, sizeof(FileHeader));
	if (f.Type != 0x4D42)
		return false;
	stream.read((char *)&i, sizeof(InfoHeader));
	if (i.BitCount != 24)
		return false;
	size = { i.Width, i.Height };
	length = i.Width * i.Height * 3;

	stream.seekg(f.OffBits, stream.beg);
	return true;
}

unsigned char *BMP::ReadData(unsigned long length)
{
	unsigned char *data = new unsigned char[length]; // NEED TO BE DELETED.
	stream.read((char *)data, length);

	return data;
}

void BMP::ToTexture(wchar_t *path, TextureBase *texture, FileReadOption option)
{
	if (stream.is_open())
		stream.close();
	stream.open(path, stream.in | stream.binary | stream._Nocreate);

	Size size;
	unsigned long dataLength;
	if (InitHeader(size, dataLength))
	{
		unsigned char *data = ReadData(dataLength);

		texture->Set(dataLength, data, size, TextureBase::PixelFormat::BGR, TextureBase::ByteSize::UByte);
		if ((option & FileReadOption::NoGenerate) == FileReadOption::None)
			texture->Generate();
	}
	if ((option & FileReadOption::NoClose) == FileReadOption::None)
		stream.close();
}
_L_END