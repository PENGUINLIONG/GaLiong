//
//  Bmp.hpp
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
	: _Bitmap(instance.Interpret(PixelType::Bgr), instance.GetSize(), instance.GetPixelType(), false)
	{
    }
	Bmp::Bmp(Buffer buffer, BufferLength length, bool shouldDelete)
	: _Bitmap(Init(buffer, length, shouldDelete))
	{
	}
    Bmp::~Bmp()
    {
	}

/*    TextureRef Bmp::ToTexture(wchar_t *path, Flag option)
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
    }*/
	
    // Derived from [LiongFramework::Media::Image]
	
	Buffer Bmp::GetChunk(Point position, Size size)
	{
		return _Bitmap.GetChunk(position, size);
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
    
    // Private
    
    Bitmap Bmp::Init(Buffer buffer, BufferLength length, bool shouldDelete)
    {
		if (length < 54)
			throw InvalidFormatException("Incomplete header.");
        if (buffer[0] != 'B' || buffer[1] != 'M')
            throw InvalidFormatException("Unsupported bmp format.");
		if (*((unsigned short*)(buffer + 28)) != 24) // Bits per pixel.
            throw InvalidFormatException("Unsupported pixel type.");
		
        unsigned int offset = *((unsigned int*)(buffer + 10));
        Size size = { *((int*)(buffer + 18)), *((int*)(buffer + 22)) };
        
		return Bitmap(buffer + offset, size, PixelType::Bgr);
		
        if (shouldDelete)
			::delete [] buffer;
    }

}
_L_END