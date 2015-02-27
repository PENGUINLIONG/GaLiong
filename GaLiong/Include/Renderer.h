#pragma once
#include "Preprocess.h"
#include "Texture.h"
////#include "TextureBuffer.h"

_L_BEGIN
class _L_ Renderer
{
public:
	enum class ReverseMethod
	{
		None,
		Horizontal,
		Vertical,
		BothDirection
	};
	static void DrawRectangle(TextureID textureID, RectD rect, ReverseMethod reverseMethod = ReverseMethod::None, SizeD textureCoord = { 1.0, 1.0 });
	static void DrawBackGroundImage(TextureBase &texture);
	static void DrawWithoutTexture(RectD rect);
	static void DrawTestImage();
};
_L_END
