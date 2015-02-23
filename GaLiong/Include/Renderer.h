#pragma once
#include "Preprocess.h"
#include "Texture.h"
#include "TextureBuffer.h"

_L_BEGIN
class _L_ Renderer
{
public:
	static void DrawRectangle(TextureID textureID, RectD rect);
	static void DrawRectangleUpsideDown(TextureID textureID, RectD rect);
	static void DrawRectangleLaterallyReversed(TextureID textureID, RectD rect);
	static void DrawRectangleCompletelyReversed(TextureID textureID, RectD rect);
	static void DrawBackGroundImage(TextureBase &texture);
	static void DrawWithoutTexture(RectD rect);
	static void DrawTestImage();
};
_L_END
