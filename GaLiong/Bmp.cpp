//
//  Bitmap.hpp
//  GaLiong
//
//  Created by Liong on ??/??/??.
//

#include "Include/Bmp.hpp"

_L_BEGIN
namespace Media
{
	// Public

    Bmp::Bmp(Image& instance)
    {
		
    }
    Bmp::~Bmp()
    {
    }

    bool Bmp::InitHeader()
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

    Buffer Bmp::ReadData(BufferLength length)
    {
        Buffer data = new Byte[length]; // NEED TO BE DELETED.
        stream.read((char *)data, length);

        return data;
    }

    TextureRef Bmp::ToTexture(wchar_t *path, Flag option)
    {
        Log << L"Bmp: Try loading " << path << L"...";
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
            Log.Log((L"Bmp: Failed in loading " + wstring(path) + L"!").c_str(), Logger::WarningLevel::Warn);
            return TextureRef();
        }

        if ((option & FileReadOption::NoClose) == FileReadOption::None)
            stream.close();
        Log << L"Bmp: Succeeded!";
        return ref;
    }
	
    // Derived from [LiongFramework::Media::Image]
	
	Buffer Bmp::GetChunk(Point position, Size size)
	{
		return _Bitmap::GetChunk(position, size);
	}
	
	BufferLength Bmp::GetInterpretedLength(PixelType pixelType)
	{
		return _Bitmap.GetInterpretedLength(pixelType);
	}
	
	Byte* Bmp::GetPixel(Point position)
	{
        return _Bitmap.GetPixel(position);
	}
	
	Size Bmp::GetSize()
	{
		return _Bitmap.GetSize();
	}
	
	bool Bmp::IsEmpty()
	{
		return _Bitmap.IsEmpty();
	}
	
	Buffer Bmp::Interpret(PixelType pixelType)
	{
		return _Bitmap.Interpret(pixelType);
	}

}
_L_END