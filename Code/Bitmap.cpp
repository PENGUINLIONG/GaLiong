//
//  Bitmap.cpp
//  GaLiong
//
//  Created by Liong on 15/10/26.
//

#include "Include/Bitmap.hpp"
_L_BEGIN
namespace Media
{
	// Public
	
	Bitmap::Bitmap(Image& instance)
	: _Data(instance.Interpret(instance.GetPixelType()))
	, _Length(instance.GetInterpretedLength(instance.GetPixelType()))
	, _PixelType(instance.GetPixelType())
	, _Size(instance.GetSize())
	{
	}
	Bitmap::Bitmap(Buffer buffer, Size size, PixelType pixelType, bool shouldCopy, bool shouldDelete)
	: _Data(shouldCopy ? ::new Byte[CalculateDataLength(size, pixelType)] : buffer)
	, _Length(CalculateDataLength(size, pixelType))
	, _PixelType(pixelType)
	, _Size(size)
	{
		if (shouldCopy)
			memcpy(_Data, buffer, _Length);
		if(shouldDelete)
			::delete [] buffer;
	}
	Bitmap::~Bitmap()
	{
		::delete [] _Data;
	}
	
	// Static
	
	Image* Bitmap::FromMemory(MemoryStream& stream, Size size, PixelType pixelType)
	{
		BufferLength length = CalculateDataLength(size, pixelType);
		Buffer buffer = stream.Read(length);
		
		return ::new Bitmap(buffer, size, pixelType);
	}
	
	// Derived from [LiongFramework::Media::Image]
	
	Buffer Bitmap::GetChunk(Point position, Size size)
	{
		if (position.X < 0 || position.X + size.Width > _Size.Width ||
			position.Y < 0 || position.Y + size.Height > _Size.Height)
			return nullptr;
		
		Buffer buffer = ::new Byte[CalculateDataLength(size, _PixelType)];
		
		long pixelLength = CalculatePixelLength(_PixelType);
		long lineData = size.Width * pixelLength;
		long lineOffset = (_Size.Width - size.Width) * pixelLength;
		Byte* pos = _Data + // Origin
			(position.X + position.Y * _Size.Width) * pixelLength; // Offset
		
		while (size.Height-- > 0)
		{
			memcpy(buffer, pos, lineData); // Copy linear pixels in the same row.
			pos += lineOffset;
		}
		
		return buffer;
	}
	
	BufferLength Bitmap::GetInterpretedLength(PixelType pixelType)
	{
		return CalculateDataLength(_Size, pixelType);
	}
	
	Byte* Bitmap::GetPixel(Point position)
	{
		BufferLength pixelLength = CalculatePixelLength(_PixelType);
		Buffer pixel = ::new Byte[pixelLength];
		memcpy(pixel, _Data + position.Y * _Size.Width + position.X, pixelLength);

		return pixel;
	}
	
	Size Bitmap::GetSize()
	{
		return _Size;
	}
	
	bool Bitmap::IsEmpty()
	{
		return _Size.Width == 0 || _Size.Height == 0;
	}
	
	Buffer Bitmap::Interpret(PixelType pixelType)
	{
		if (pixelType == _PixelType)
		{
			Buffer buffer = ::new Byte[_Length];
			memcpy(buffer, _Data, _Length);
			return buffer;
		}
		
		switch (CalculatePixelLength(_PixelType))
		{
			case 1:
				return InterpretMonoTo(pixelType);
			case 3:
				return InterpretTriTo(pixelType);
			case 4:
				return InterpretQuadTo(pixelType);
		}
		return nullptr;
	}
	
	// Derived from [LiongFramework::Serialization::ISerializable<Bitmap>]
	
	Bitmap* Bitmap::Deserialize(Buffer data, BufferLength length)
	{
		if (length < 3)
			return nullptr;
		Size size = {((int*)data)[0], ((int*)data)[1]};
		PixelType pixelType = (PixelType)((int*)data)[2];
		length -= 3 * sizeof(int); // Omit the information bytes.
		if (length != CalculateDataLength(size, pixelType))
			return nullptr;
		Buffer buffer = ::new Byte[length];
		return ::new Bitmap(buffer, size, pixelType);
	}
	
	Buffer Bitmap::Serialize()
	{
		Buffer buffer = ::new Byte[_Length + 3];
		((int*)buffer)[0] = (int)_Size.Width;
		((int*)buffer)[1] = (int)_Size.Height;
		((int*)buffer)[2] = _PixelType;
		memcpy(buffer + 3 * sizeof(int), _Data, _Length);
		return buffer;
	}
	
	// Private
	
	Buffer Bitmap::InterpretMonoTo(PixelType pixelType)
	{
		if (pixelType < 4) return nullptr; // Mono
		else if (pixelType == PixelType::Rgba) // Quad
			return InterpretMonoToQuad((int)pixelType);
		else // Tri
			return InterpretMonoToTri(pixelType == PixelType::Rgb
									  ? (int)pixelType - 1
									  : 3 - (int)pixelType);
	}
	
	Buffer Bitmap::InterpretTriTo(PixelType pixelType)
	{
		if (pixelType == PixelType::Rgba) // Quad
			return InterpretTriToQuad((bool)(pixelType - 4));
		else if ((int)pixelType < 4 && pixelType != PixelType::Alpha) // Mono
			return InterpretTriToMono(_PixelType == PixelType::Rgb);
		else // Tri
            return InterpretTriToTri();
	}
	
	Buffer Bitmap::InterpretQuadTo(PixelType pixelType)
	{
		if (pixelType < 4) // Mono
            return InterpretQuadToMono((int)pixelType);
        else // Tri
            return InterpretQuadToTri((bool)(pixelType - 4));
	}
	
	Buffer Bitmap::InterpretMonoToTri(long factorOffset)
	{
		if (factorOffset < 0)
			return nullptr;
		Buffer buffer = ::new Byte[_Size.Width * _Size.Height * 3];
		for (int i = 0; i < _Length; ++i)
			buffer[i * 3 + factorOffset] = _Data[i];
		return buffer;
	}
	
	Buffer Bitmap::InterpretMonoToQuad(long factorOffset)
	{
		Buffer buffer = ::new Byte[_Size.Width * _Size.Height * 4];
		for (int i = 0; i < _Length; ++i)
		{
			buffer[i * 4 + factorOffset] = _Data[i];
			buffer[i * 4 + 3] = 0xFF;
		}
		return buffer;
	}
	
	Buffer Bitmap::InterpretTriToMono(long factorOffset)
	{
        long pixelCount = _Size.Width * _Size.Height;
		Buffer buffer = ::new Byte[pixelCount];
		for (int i = 0; i < pixelCount; ++i)
			buffer[i] = _Data[i * 3 + factorOffset];
		return buffer;
	}
	
	Buffer Bitmap::InterpretTriToTri()
	{
        long pixelCount = _Size.Width * _Size.Height * 3;
        Buffer buffer = ::new Byte[pixelCount];
        for (int i = 0; i < pixelCount; i += 3)
        {
            buffer[i] = _Data[i + 2];
            buffer[i + 1] = _Data[i + 1];
            buffer[i + 2] = _Data[i];
        }
        return buffer;
	}
    
    Buffer Bitmap::InterpretTriToQuad(bool shouldInverse)
    {
        long pixelCount = _Size.Width * _Size.Height;
        Buffer buffer = ::new Byte[pixelCount * 4];
        if (shouldInverse)
        {
            for (int i = 0; i < pixelCount; ++i)
            {
                buffer[i * 4] = _Data[i * 3];
                buffer[i * 4 + 1] = _Data[i * 3 + 1];
                buffer[i * 4 + 2] = _Data[i * 3 + 2];
				buffer[i * 4 + 3] = 0xFF;
            }
        }
        else
        {
            for (int i = 0; i < pixelCount; ++i)
            {
                buffer[i * 4] = _Data[i * 3 + 2];
                buffer[i * 4 + 1] = _Data[i * 3 + 1];
                buffer[i * 4 + 2] = _Data[i * 3];
				buffer[i * 4 + 3] = 0xFF;
            }
        }
        return buffer;
    }
    
    Buffer Bitmap::InterpretQuadToMono(long factorOffset)
    {
        long pixelCount = _Size.Width * _Size.Height;
        Buffer buffer = ::new Byte[pixelCount];
        for (int i = 0; i < pixelCount; ++i)
            buffer[i] = _Data[i * 4 + factorOffset];
        return buffer;
    }
    
    Buffer Bitmap::InterpretQuadToTri(bool shouldInverse)
    {
        long pixelCount = _Size.Width * _Size.Height;
        Buffer buffer = ::new Byte[pixelCount * 3];
        if (shouldInverse)
        {
            for (int i = 0; i < pixelCount; ++i)
            {
                buffer[i * 3] = _Data[i * 4];
                buffer[i * 3 + 1] = _Data[i * 4 + 1];
                buffer[i * 3 + 2] = _Data[i * 4 + 2];
            }
        }
        else
        {
            for (int i = 0; i < pixelCount; ++i)
            {
                buffer[i * 3] = _Data[i * 4 + 2];
                buffer[i * 3 + 1] = _Data[i * 4 + 1];
                buffer[i * 3 + 2] = _Data[i * 4];
            }
        }
        return buffer;
    }
	
	// Static
	
	long Bitmap::CalculatePixelLength(PixelType pixelType)
	{
		switch (pixelType)
		{
			case PixelType::Rgba:
				return 4;
			case PixelType::Bgr:
			case PixelType::Rgb:
				return 3;
			case PixelType::Alpha:
			case PixelType::Red:
			case PixelType::Green:
			case PixelType::Blue:
				return 1;
			default:
				return 0;
		}
	}
	
	long Bitmap::CalculateDataLength(Size size, PixelType pixelType)
	{
		return size.Width * size.Height * CalculatePixelLength(pixelType);
	}
}
_L_END
