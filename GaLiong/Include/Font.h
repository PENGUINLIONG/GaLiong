#pragma once
#include "Preprocess.h"
#include "Texture.h"
#include "TextureBuilder.h"

_L_BEGIN
class _L_ Font
{
public:
	friend class LibFreeType;
	Font();
	void SetSizeQ26_6(Size size);
	void SetSizeQ26_6(Size size, unsigned int resolution_X, unsigned int resolution_Y);
	void SetSizeAbsolute(Size size);
	void SetColor(Color fontColor, Color outlineColor);
	void SetOutlineWidth(double width);
	Texture *RenderString(const wchar_t *text, Size border, Size *spare = nullptr);
	~Font();
#ifdef _INSIDER_COMPILATION
private:
	unsigned char *file;
	double outlineWidth = 0;
	Size size;
	Color fontColor, outlineColor;
	FT_Face face;
	FT_Stroker stroker;
#endif
};
_L_END
