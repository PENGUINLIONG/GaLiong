#pragma once
#include "Preprocess.h"
#include "Texture.h"
#include "TextureBuffer.h"

_L_BEGIN
class _L_ Renderer
{
public:
	Renderer();
	void DrawRectangle(GLuint textureID, RectD rect);
	void DrawRectangleUpsideDown(GLuint textureID, RectD rect);
	void DrawBackGroundImage(Texture &texture);
	void DrawBackGroundImage(TextureBuffer &texture);
	void DrawWithoutTexture(RectD rect);
	void Resize(Size size);
	void DrawTestImage();
	~Renderer();
private:
	Size window;
};
_L_END