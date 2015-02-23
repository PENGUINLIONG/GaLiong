#include "TextBar.h"

_L_BEGIN
TextBar::TextBar()
{
}
TextBar::~TextBar()
{
}

void TextBar::BindTexture(TextureBase *texture)
{
	Entity::BindTexture(texture);
}

void TextBar::BindBorderTexture(TextureBase *texture)
{

}
_L_END