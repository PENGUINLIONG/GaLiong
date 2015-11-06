//
//  Bitmap.hpp
//  GaLiong
//
//  Created by Liong on 15/10/26.
//

#ifndef Bitmap_hpp
#define Bitmap_hpp

#include "Preprocess.hpp"
#include "Image.hpp"
#include "ISerializable.h"

using namespace LiongFramework::Serialization;

_L_BEGIN
namespace Media
{
	/*
	 * [note] This class is a simple storage of pixel sequence so it is not able to analyze the file format whose extension is '.bmp'. To do that, please use [LiongFramework::Media::Bmp] instead.
	 */
	class _L_ Bitmap
    : public Image
    , public ISerializable<Bitmap>
	{
	public:
		Bitmap(Image& image);
		Bitmap(Buffer buffer, Size size, PixelType pixelType, bool shouldCopy = true, bool shouldDelete = true);
		virtual ~Bitmap();
        
        // Static
        
        /*
		 * Create a new instance of [LiongStudio::Media::Bitmap].
		 * [warning] You should delete the pointer when you will not use it anymore.
		 */	
		static Image* FromMemory(MemoryStream& stream, Size size, PixelType pixelType);
        
        // Derived from [LiongFramework::Media::Image]
		
        virtual Buffer GetChunk(Point position, Size size) override;
		virtual BufferLength GetInterpretedLength(PixelType pixelType) override;
        virtual Buffer GetPixel(Point position) override;
		virtual Size GetSize() override;
		virtual PixelType GetPixelType() override;
		virtual bool IsEmpty() override;
        virtual Buffer Interpret(PixelType pixelType) override;
        
        // Derived from [LiongFramework::Serialization::ISerializable<Bitmap>]
		
		// [note] Image size information will be converted to ints, so they may become invalid if the number of height or height is too large.
		
		// [architecture] The serialized form of this type of image is very simple as there is few information should be stored.
		// [4] Width of image(int)
		// [4] Height of image(int)
		// [4] PixelType(int)
		// [~] Pixels
		
		virtual Bitmap* Deserialize(Buffer buffer, BufferLength bufferLength) override;
        virtual Buffer Serialize() override;
	private:
		Buffer _Data;
		BufferLength _Length;
		PixelType _PixelType;
		Size _Size;
		
		Buffer InterpretMonoTo(PixelType pixelType);
		Buffer InterpretTriTo(PixelType pixelType);
		Buffer InterpretQuadTo(PixelType pixelType);
		
		Buffer InterpretMonoToTri(long factorOffset);
		Buffer InterpretMonoToQuad(long factorOffset);
		
		Buffer InterpretTriToMono(long factorOffset);
		Buffer InterpretTriToTri();
		Buffer InterpretTriToQuad(bool shouldInverse);
		
		Buffer InterpretQuadToMono(long factorOffset);
		Buffer InterpretQuadToTri(bool shouldInverse);
		
        // Static
		
		static long CalculatePixelLength(PixelType pixelType);
		static long CalculateDataLength(Size size, PixelType pixelType);
	};
}
_L_END
#endif /* Bitmap_hpp */
