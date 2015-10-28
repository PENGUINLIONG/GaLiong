//
//  Bitmap.hpp
//  GaLiong
//
//  Created by Liong on ??/??/??.
//

#ifndef Bmp_hpp
#define Bmp_hpp

#include "Preprocess.hpp"
#include "Bitmap.hpp"
#include "Image.hpp"

_L_BEGIN
namespace Media
{
	class _L_ Bmp
	: public Image
	{
	public:
		struct FileHeader
		{
			Byte2 Type;
			Byte4 Size;
			Byte2 Reserved1;
			Byte2 Reserved2;
			Byte4 Offset;
		};
		struct InfoHeader
		{
			Byte4 Size;
			int Width;
			int Height;
			Byte2 Planes;
			Byte2 BitCount;
			Byte4 Compression;
			Byte4 SizeImage;
			int XPelsPerMeter;
			int YPelsPerMeter;
			Byte4 ClrUsed;
			Byte4 ClrImportant;
		};

		Bmp(Image& instance);
		~Bmp();
		bool InitHeader(Size &size, BufferLength &length);
		Buffer ReadData(BufferLength length);
		TextureRef ToTexture(wchar_t *path, Flag option = FileReadOption::None);
		
		// Derived from [LiongFramework::Media::Image]
		
		virtual Buffer GetChunk(Point position, Size size) override;
		virtual BufferLength GetInterpretedLength(PixelType pixelType) override;
		virtual Buffer GetPixel(Point position) override;
		virtual Size GetSize() override;
		virtual PixelType GetPixelType() override;
		virtual bool IsEmpty() override;
		virtual Buffer Interpret(PixelType pixelType) override;
	private:
		FileHeader _FileHeader;
		InfoHeader _InfoHeader;
		Bitmap _Bitmap;
    };
}
_L_END
#endif