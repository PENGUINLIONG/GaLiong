 #include "BMP.hpp"

_L_BEGIN
BMP::BMP() {}
BMP::~BMP() {}

bool BMP::InitHeader(Size &size, BufferLength &length)
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

Buffer BMP::ReadData(BufferLength length)
{
	Buffer data = new Byte[length]; // NEED TO BE DELETED.
	stream.read((char *)data, length);

	return data;
}

TextureRef BMP::ToTexture(wchar_t *path, Flag option)
{
	Log << L"BMP: Try loading " << path << L"...";
	if (stream.is_open())
		stream.close();
	stream.open(path, stream.in | stream.binary | stream._Nocreate);

	TextureRef ref;

	Size size;
	BufferLength dataLength;
	if (InitHeader(size, dataLength))
	{
		Buffer data = ReadData(dataLength);
		if (!data)
			return TextureRef();

		ref = TextureManager.NewTexture(dataLength, data, size, Texture::PixelFormat::BGR, Texture::ByteSize::UByte);
		if ((option & FileReadOption::NoGenerate) == FileReadOption::None)
			ref.lock()->Generate();
	}
	else
	{
		Log.Log((L"BMP: Failed in loading " + wstring(path) + L"!").c_str(), Logger::WarningLevel::Warn);
		return TextureRef();
	}

	if ((option & FileReadOption::NoClose) == FileReadOption::None)
		stream.close();
	Log << L"BMP: Succeeded!";
	return ref;
}
_L_END