#pragma once
#include "Preprocess.hpp"
#include "Texture.hpp"
////#include "TextureBuffer.hpp"

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
	static void DrawRectangle(TextureIndex textureID, RectD rect, ReverseMethod reverseMethod = ReverseMethod::None, SizeD textureCoord = { 1.0, 1.0 });
	static void DrawBackGroundImage(TextureRef texture);
	static void DrawWithoutTexture(RectD rect);
	static void DrawTestImage();
};
_L_END