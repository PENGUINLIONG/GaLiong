#include "Font.h"

_L_BEGIN
Font::Font()
{
}

void Font::SetSizeQ26_6(Size size)
{
	FT_Set_Char_Size(face, size.Width, size.Height, 72, 72);
}

void Font::SetSizeQ26_6(Size size, unsigned int resolution_X, unsigned int resolution_Y)
{
	FT_Set_Char_Size(face, size.Width, size.Height, resolution_X, resolution_Y);
	this->size = { size.Width >> 6, size.Height >> 6 };
}

void Font::SetSizeAbsolute(Size size)
{
	FT_Set_Pixel_Sizes(face, size.Width, size.Height);
	this->size = size;
}

void Font::SetColor(Color fontColor, Color outlineColor)
{
	if (fontColor.Red || fontColor.Green || fontColor.Blue || fontColor.Alpha)
		this->fontColor = fontColor;
	if (outlineColor.Red || outlineColor.Green || outlineColor.Blue || outlineColor.Alpha)
		this->outlineColor = outlineColor;
}

void Font::SetOutlineWidth(double width)
{
	outlineWidth = width;
	FT_Stroker_Set(stroker, width * 64.0, FT_STROKER_LINECAP_ROUND, FT_STROKER_LINEJOIN_ROUND, 0);
}

TextureRef Font::RenderString(const wchar_t *text, Size border, Size *spare)
{
	if (border.Width == 0)
		border.Width = MAXLONG;
	if (border.Height == 0)
		border.Height = MAXLONG;

	FT_Glyph glyph, _glyph;
	unsigned long strLength = wcslen(text);
	
	long ceiling = 0;
	FT_UInt previousIndex = 0;
	Point offset = { 0, 0 };
	Size advance = { 0, 0 };

	TextureRef texture(nullptr);
	TextureBuilder builder(TextureBase::PixelFormat::RGBA, TextureBase::ByteSize::UByte);

#pragma region Process the text
	for (unsigned long i = 0; i < strLength; i++)
	{
		if (*(text + i) == L'\n')
		{
			offset.X = 0;
			offset.Y -= advance.Height;
			continue;
		}

#pragma region Initialization
		long dstOffset = 0,
			srcOffset = 0;
		Size outlineOffset = { 0, 0 },
			outlineOffset_doubled = { 0, 0 };

		FT_Vector delta = { 0, 0 };
		FT_UInt index = FT_Get_Char_Index(face, *(text + i));
		Rect rect;
		FT_BitmapGlyph bitmapGlyph, _bitmapGlyph;
		FT_Bitmap bitmap, _bitmap;
#pragma endregion

		if (FT_Load_Glyph(face, index, FT_LOAD_RENDER | FT_LOAD_TARGET_NORMAL))
			throw exception("Failed in rendering font glyph.");
		FT_Get_Glyph(face->glyph, &glyph);

		// Get the rendered glyph.
		FT_Glyph_To_Bitmap(&glyph, FT_RENDER_MODE_NORMAL, nullptr, true);
		bitmapGlyph = reinterpret_cast<FT_BitmapGlyph>(glyph);
		bitmap = bitmapGlyph->bitmap;

		if (bitmap.rows > ceiling && !offset.Y)
			ceiling = bitmap.rows;

		// Kerning.
		if (previousIndex) // If the current glyph is not the first one in the $text,
			// Make the final output more aesthetic.
			FT_Get_Kerning(face, previousIndex, index, FT_KERNING_DEFAULT, &delta);
		offset.X += (delta.x >> 6);

#pragma region Avoid the risk
		// Check whether the bitmap is empty.
		if (!bitmap.width || !bitmap.rows)
		{
			offset.X += face->glyph->metrics.horiAdvance >> 6;
			continue;
		}
		
		// Check whether the current glyph gets out of the max size in X coord.
		if ((face->glyph->metrics.horiAdvance >> 6) + offset.X > border.Width)
		{
			offset.X = 0;
			offset.Y -= advance.Height;
		}
		
		// Check whether the current glyph gets out of the max size in Y coord.
		if (bitmap.rows - bitmapGlyph->top - offset.Y + ceiling > border.Height)
		{
			FT_Done_Glyph(glyph);
			break;
		}
#pragma endregion

		BufferLength length;
		Buffer buffer;

		if (outlineWidth)
		{
#pragma region Outline
			// Draw the outline.
			if (FT_Load_Glyph(face, index, FT_LOAD_NO_BITMAP))
				throw exception("Failed in rendering font glyph.");
			FT_Error e = FT_Get_Glyph(face->glyph, &_glyph);

			FT_Glyph_Stroke(&_glyph, stroker, true);

			FT_Glyph_To_Bitmap(&_glyph, FT_RENDER_MODE_NORMAL, nullptr, true);
			_bitmapGlyph = reinterpret_cast<FT_BitmapGlyph>(_glyph);
			_bitmap = _bitmapGlyph->bitmap;

			outlineOffset_doubled = { _bitmap.width - bitmap.width, _bitmap.rows - bitmap.rows };
			outlineOffset = { outlineOffset_doubled.Width >> 1, outlineOffset_doubled.Height >> 1 };

			length = (_bitmap.width * _bitmap.rows) << 2;
			// The buffer will be deleted in 'Texture' so just keep it alive.
			buffer = new Byte[length];
			memset(buffer, 0, length);

#pragma region Transfer data
			for (long y = 0; y < _bitmap.rows; y++)
			{
				for (long x = 0; x < _bitmap.width; x++)
				{
					unsigned char alpha = *(_bitmap.buffer + srcOffset);
					if (alpha)
					{
						*(buffer + dstOffset + 0) = outlineColor.Red;
						*(buffer + dstOffset + 1) = outlineColor.Green;
						*(buffer + dstOffset + 2) = outlineColor.Blue;
						*(buffer + dstOffset + 3) = alpha;
					}
					dstOffset += 4;
					srcOffset++;
				}
			}
#pragma endregion

#pragma region Cover the glyph on
			// Blending.
			dstOffset = (_bitmap.width * outlineOffset.Height + outlineOffset.Width) << 2;
			srcOffset = 0;

			for (long y = 0; y < bitmap.rows; y++)
			{
				for (long x = 0; x < bitmap.width; x++)
				{
					unsigned char alpha = *(bitmap.buffer + srcOffset);
					if (alpha)
					{
						Buffer pixel = buffer + dstOffset;
						*(pixel + 0) = (unsigned char)((unsigned short)(*(pixel + 0) * (255 - alpha)) >> 8) +
							(unsigned char)(((unsigned short)(fontColor.Red * alpha)) >> 8) + 1;
						*(pixel + 1) = (unsigned char)((unsigned short)(*(pixel + 1) * (255 - alpha)) >> 8) +
							(unsigned char)(((unsigned short)(fontColor.Green * alpha)) >> 8) + 1;
						*(pixel + 2) = (unsigned char)((unsigned short)(*(pixel + 2) * (255 - alpha)) >> 8) +
							(unsigned char)(((unsigned short)(fontColor.Blue * alpha)) >> 8) + 1;
						*(pixel + 3) = (unsigned char)((unsigned short)(*(pixel + 3) * (255 - alpha)) >> 8) +
							(unsigned char)(((unsigned short)(alpha * alpha)) >> 8) + 1;
					}
					dstOffset += 4;
					srcOffset++;
				}
				dstOffset += outlineOffset_doubled.Width << 2;
			}
#pragma endregion
			
			rect = {
				offset.X + _bitmapGlyph->left,
				offset.Y + _bitmapGlyph->top,
				offset.X + _bitmapGlyph->left + _bitmap.width,
				offset.Y + _bitmapGlyph->top - _bitmap.rows
			};

			FT_Done_Glyph(_glyph);
#pragma endregion
		}
		else 
		{
#pragma region No outline
			length = (bitmap.width * bitmap.rows) << 2;
			// The buffer will be deleted in 'Texture' so just keep it alive.
			buffer = new Byte[length];
			memset(buffer, 0, length);

#pragma region Transfer data
			for (long y = 0; y < bitmap.rows; y++)
			{
				for (long x = 0; x < bitmap.width; x++)
				{
					unsigned char alpha = *(bitmap.buffer + srcOffset);
					if (alpha)
					{
						*(buffer + dstOffset + 0) = outlineColor.Red;
						*(buffer + dstOffset + 1) = outlineColor.Green;
						*(buffer + dstOffset + 2) = outlineColor.Blue;
						*(buffer + dstOffset + 3) = alpha;
					}
					dstOffset += 4;
					srcOffset++;
				}
			}
#pragma endregion

			rect = {
				offset.X + bitmapGlyph->left,
				offset.Y + bitmapGlyph->top,
				offset.X + bitmapGlyph->left + bitmap.width,
				offset.Y + bitmapGlyph->top - bitmap.rows
			};
#pragma endregion
		}
		
		advance.Width = (face->glyph->metrics.horiAdvance >> 6) + outlineOffset_doubled.Width;
		if ((face->glyph->metrics.vertAdvance >> 6) + outlineOffset_doubled.Width > advance.Height)
			advance.Height = (face->glyph->metrics.vertAdvance >> 6) + outlineOffset_doubled.Width;

		offset.X += advance.Width;

		Size used = { bitmap.width + outlineOffset_doubled.Width, bitmap.rows + outlineOffset_doubled.Height };
		texture = make_shared<Texture>();
		texture->Set(length,
			buffer,
			used,
			Texture::PixelFormat::RGBA,
			Texture::ByteSize::UByte);
		builder.AppendConponent({ rect, texture });

		if (spare)
		{
			spare->Width = border.Width - used.Width;
			spare->Height = border.Height - used.Height;
		}

		FT_Done_Glyph(glyph);

		previousIndex = index;
	}
#pragma endregion
	
	builder.Make(texture);
	if (texture && texture->IsAvailable())
		texture->Generate(Texture::Filter::Nearest);
	
	return texture;
}

Font::~Font()
{
	FT_Stroker_Done(stroker);
	FT_Done_Face(face);
	delete[] file;
}
_L_END