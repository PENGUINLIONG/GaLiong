//
//  Image.hpp
//  GaLiong
//
//  Created by Liong on 15/10/25.
//

#ifndef Image_hpp
#define Image_hpp

#include "Preprocess.hpp"
#include "MemoryStream.hpp"

_L_BEGIN
using namespace LiongFramework::IO;

namespace Media
{
	enum PixelType
	{
		Alpha = 0,
		Red = 1,
		Green = 2,
		Blue = 3,
		Rgb = 4,
		Bgr = 5,
		Argb = 6
	};
	
	class _L_ Image
	{
	public:
		/*
		 * Retrieve a chunk of pixels in the image.
		 * [return] A pointer to a newly allocated buffer which stores sequense of pixels.
		 * [warning] You should delete the pointer when you will not use it anymore.
		 * [note] You should not use this method to retrieve a chunk of pixels. Alternatively, use [LiongFramework::IO::Image::GetChunk] instead.
		 */
		virtual Buffer GetChunk(Point position, Size size) = 0;
		virtual BufferLength GetInterpretedLength(PixelType pixelType) = 0;
		/*
		 * Retrieve a single pixel in the image.
		 * [return] A pointer to a newly allocated buffer which stores a single pixel.
		 * [warning] You should delete the pointer when you will not use it anymore.
		 * [note] You should not use this method to retrieve a chunk of pixels. Alternatively, use [LiongFramework::IO::Image::GetChunk] instead.
		 */
		virtual Buffer GetPixel(Point position) = 0;
		virtual Size GetSize() = 0;
		virtual PixelType GetPixelType() = 0;
		virtual bool IsEmpty() = 0;
		/*
		 * Interpret data to Bitmap of a specific pixel type and save the result into a newly allocated buffer.
		 * [return] A pointer to a newly allocated which stores sequense of pixels of the same specified type.
		 * [warning] You should delete the pointer when you will not use it anymore.
		 */
		virtual Buffer Interpret(PixelType pixelType) = 0;
	};
}
_L_END

#endif /* Image_hpp */
