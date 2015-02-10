#pragma once
#include "Preprocess.h"
#include "TextureBuilder.h"

_L_BEGIN


class _L_ Font
{
public:
	Font(unsigned char *file, unsigned long length, long index, FT_Library library);
	inline void SetSizeQ26_6(Size size)
	{
		FT_Set_Char_Size(face, size.Width, size.Height, 72, 72);
	}
	inline void SetSizeQ26_6(Size size, unsigned int resolution_X, unsigned int resolution_Y)
	{
		FT_Set_Char_Size(face, size.Width, size.Height, resolution_X, resolution_Y);
		this->size = { size.Width >> 6, size.Height >> 6 };
	}
	inline void SetSizeAbsolute(Size size)
	{
		FT_Set_Pixel_Sizes(face, size.Width, size.Height);
		this->size = size;
	}
	inline void SetColor(Color fontColor, Color outlineColor)
	{
		if (fontColor.Red || fontColor.Green || fontColor.Blue || fontColor.Alpha)
			this->fontColor = fontColor;
		if (outlineColor.Red || outlineColor.Green || outlineColor.Blue || outlineColor.Alpha)
			this->outlineColor = outlineColor;
	}
	inline void SetOutlineWidth(double width)
	{
		outlineWidth = width;
		FT_Stroker_Set(stroker, width * 64.0, FT_STROKER_LINECAP_ROUND, FT_STROKER_LINEJOIN_ROUND, 0);
	}
	Texture *RenderString(wchar_t *text, Size border);
	~Font();
private:
	unsigned char *file;
	double outlineWidth = 0;
	Size size;
	Color fontColor, outlineColor;
	FT_Face face;
	FT_Stroker stroker;
};
_L_END