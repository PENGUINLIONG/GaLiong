#include "Font.h"

_L_BEGIN
Font::Font(unsigned char *file, unsigned long length, long index, FT_Library library)
{
	this->file = file;
	FT_New_Memory_Face(library, file, length, index, &face);
	FT_Select_Charmap(face, FT_ENCODING_UNICODE);
	FT_Stroker_New(library, &stroker);
	size = { 0, 0 };
	fontColor = outlineColor = { 0xFF, 0xFF, 0xFF, 0xFF };
}

Texture *Font::RenderString(wchar_t *text)
{
	if (!fontColor.Alpha) // If font color is null, there will be nothing happen.
		fontColor.Alpha = 0xFF;

	FT_Glyph glyph, _glyph;
	unsigned long strLength = wcslen(text);
	FT_UInt previousIndex = 0;
	Point offset = { 0, 0 };

	Texture *texture = nullptr;
	TextureBuilder builder(GL_RGBA, GL_UNSIGNED_BYTE);

	for (unsigned int i = 0; i < strLength; i++)
	{
		if (*(text + i) == L' ')
		{
			offset.X += face->glyph->advance.x >> 6;
			continue;
		}

		long dstOffset = 0,
			srcOffset = 0;
		Size outlineOffset = { 0, 0 },
			outlineOffset_doubled = { 0, 0 };

		FT_Vector delta = { 0, 0 };
		FT_UInt index = FT_Get_Char_Index(face, *(text + i));
		Rect rect;
		FT_BitmapGlyph bitmapGlyph, _bitmapGlyph;
		FT_Bitmap bitmap, _bitmap;

		if (FT_Load_Glyph(face, index, FT_LOAD_NO_BITMAP))// FT_LOAD_RENDER | FT_LOAD_TARGET_NORMAL))
			throw exception("Failed in rendering font glyph.");
		FT_Get_Glyph(face->glyph, &glyph);

		// Get the rendered glyph.
		FT_Glyph_To_Bitmap(&glyph, FT_RENDER_MODE_NORMAL, nullptr, true);
		bitmapGlyph = reinterpret_cast<FT_BitmapGlyph>(glyph);
		bitmap = bitmapGlyph->bitmap;

		if (previousIndex) // If the current glyph is not the first one in the $text,
			// Make the final output more aesthetic.
			FT_Get_Kerning(face, previousIndex, index, FT_KERNING_DEFAULT, &delta);

#pragma region Outline
		// Draw the outline.
		if (FT_Load_Glyph(face, index, FT_LOAD_NO_BITMAP))// FT_LOAD_RENDER | FT_LOAD_TARGET_NORMAL))
			throw exception("Failed in rendering font glyph.");
		FT_Get_Glyph(face->glyph, &_glyph);
		
		FT_Glyph_Stroke(&_glyph, stroker, true);

		FT_Glyph_To_Bitmap(&_glyph, FT_RENDER_MODE_NORMAL, nullptr, true);
		_bitmapGlyph = reinterpret_cast<FT_BitmapGlyph>(_glyph);
		_bitmap = _bitmapGlyph->bitmap;
#pragma endregion

		outlineOffset_doubled = { _bitmap.width - bitmap.width, _bitmap.rows - bitmap.rows };
		outlineOffset = { outlineOffset_doubled.Width >> 1, outlineOffset_doubled.Height >> 1 };

		if (!bitmap.width || !bitmap.rows)
		{
			offset.X += (face->glyph->advance.x >> 6);
			continue; // Buggy, It will be executed when we met Unicode characters such as ☺.           <Important>
			// When we only use the chars which cannot be rendered,
			//     it will crash because no buffer is created.
		}

		unsigned long length = (_bitmap.width * _bitmap.rows) << 2;
		// The buffer will be deleted in 'Texture' so just keep it alive.
		unsigned char *buffer = new unsigned char[length];
		memset(buffer, 0, length);

#pragma region Home-made memcpy func
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
					unsigned char *pixel = buffer + dstOffset;
					*(pixel + 0) = (unsigned char)((unsigned short)(*(pixel + 0) * (255 - alpha)) >> 8) +
						(unsigned char)(((unsigned short)(fontColor.Red * alpha)) >> 8);
					*(pixel + 1) = (unsigned char)((unsigned short)(*(pixel + 1) * (255 - alpha)) >> 8) +
						(unsigned char)(((unsigned short)(fontColor.Green * alpha)) >> 8);
					*(pixel + 2) = (unsigned char)((unsigned short)(*(pixel + 2) * (255 - alpha)) >> 8) +
						(unsigned char)(((unsigned short)(fontColor.Blue * alpha)) >> 8);
					*(pixel + 3) = (unsigned char)((unsigned short)(*(pixel + 3) * (255 - alpha)) >> 8) +
						(unsigned char)(((unsigned short)(alpha * alpha)) >> 8);
				}
				dstOffset += 4;
				srcOffset++;
			}
			dstOffset += outlineOffset_doubled.Width << 2;
		}
#pragma endregion

		offset.X += (delta.x >> 6);

		rect = {
			offset.X + _bitmapGlyph->left,
			offset.Y + _bitmapGlyph->top,
			offset.X + _bitmapGlyph->left + _bitmap.width,
			offset.Y + _bitmapGlyph->top - _bitmap.rows
		};

		offset.X += (face->glyph->advance.x >> 6) + outlineOffset_doubled.Width;

		texture = new Texture();
#pragma region Pack up the texture
#ifdef _DEBUG
		texture->Path = text + i;
#endif
		texture->DataLength = length;
		texture->Data = buffer;
		texture->Size = { bitmap.width + outlineOffset_doubled.Width, bitmap.rows + outlineOffset_doubled.Height };
		texture->PixelFormat = GL_RGBA;
		texture->ByteSize = GL_UNSIGNED_BYTE;
#pragma endregion
		FT_Done_Glyph(_glyph);
		FT_Done_Glyph(glyph);

		builder.AppendConponent({ rect, texture });

		previousIndex = index;
	}

	return builder.Make();
}

Font::~Font()
{
	FT_Stroker_Done(stroker);
	FT_Done_Face(face);
	delete[] file;
}
_L_END