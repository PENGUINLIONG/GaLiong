#include "TextBar.h"

_L_BEGIN
#define LEFT 0
#define TOP 1
#define RIGHT 2
#define BOTTOM 3
#define UPPER_LEFT 4
#define UPPER_RIGHT 5
#define LOWER_LEFT 6
#define LOWER_RIGHT 7

TextBar::TextBar()
{
	implemented = ControlInterface::IRenderable;
	for (auto &texture_flag : textures_Border)
	{
		texture_flag = { nullptr, Renderer::ReverseMethod::None, { 0.0, 0.0, 0.0, 0.0 }, BorderComment::NoComment, { 0.0, 0.0 } };
	}
	available = true;
}
TextBar::~TextBar()
{
}

void TextBar::BindBorderTexture(TextureRef texture, const Flag comment)
{
	if (!texture || !texture->IsAvailable() || !comment)
		return;
	Size _s = texture->GetSize();
	SizeD size_Texture = { ((double)_s.Width / (double)windowSize->Height) * 100.0, ((double)_s.Height / (double)windowSize->Height) * 100.0 };
	Size size_Control = { (long)((this->size.Width / 100.0) * windowSize->Height), (long)((this->size.Height / 100.0) * windowSize->Height) };

	texture->Get().ChangeFilter(Texture::Filter::Nearest);

	if (comment & BorderComment::EveryBorder)
	{
		if (comment & BorderComment::EveryBorder == BorderComment::EveryBorder)
		{
			textures_Border[LEFT] = { texture, Renderer::ReverseMethod::None, { pos.X - size_Texture.Width, pos.Y, pos.X, pos.Y - size.Height }, comment, { 1.0, texture->CalculateDuplication(size_Control).Height } };
			textures_Border[TOP] = { texture, Renderer::ReverseMethod::None, { pos.X, pos.Y + size_Texture.Height, pos.X + size.Width + size_Texture.Width, pos.Y }, comment, { texture->CalculateDuplication(size_Control).Width, 1.0 } };
			textures_Border[RIGHT] = { texture, Renderer::ReverseMethod::Horizontal, { pos.X + size.Width, pos.Y, pos.X + size.Width + size_Texture.Width, pos.Y - size.Height }, comment, { 1.0, texture->CalculateDuplication(size_Control).Height } };
			textures_Border[BOTTOM] = { texture, Renderer::ReverseMethod::Vertical, { pos.X, pos.Y - size.Height, pos.X + size.Width, pos.Y - size.Height - size_Texture.Height }, comment, { texture->CalculateDuplication(size_Control).Width, 1.0 } };
			goto _;
		}
		if (comment & BorderComment::Left)
			textures_Border[LEFT] = { texture, Renderer::ReverseMethod::None, { pos.X - size_Texture.Width, pos.Y, pos.X, pos.Y - size.Height }, comment, { 1.0, texture->CalculateDuplication(size_Control).Height } };
		if (comment & BorderComment::Top)
			textures_Border[TOP] = { texture, Renderer::ReverseMethod::None, { pos.X, pos.Y + size_Texture.Height, pos.X + size.Width + size_Texture.Width, pos.Y }, comment, { texture->CalculateDuplication(size_Control).Width, 1.0 } };
		if (comment & BorderComment::Right)
			textures_Border[RIGHT] = { texture, Renderer::ReverseMethod::None, { pos.X + size.Width, pos.Y, pos.X + size.Width + size_Texture.Width, pos.Y - size.Height }, comment, { 1.0, texture->CalculateDuplication(size_Control).Height } };
		if (comment & BorderComment::Bottom)
			textures_Border[BOTTOM] = { texture, Renderer::ReverseMethod::None, { pos.X, pos.Y - size.Height, pos.X + size.Width, pos.Y - size.Height - size_Texture.Height }, comment, { texture->CalculateDuplication(size_Control).Width, 1.0 } };
	}

	_:
	if (comment & BorderComment::EveryCorner)
	{
		if (comment & BorderComment::EveryCorner == BorderComment::EveryCorner)
		{
			textures_Border[UPPER_LEFT] = { texture, Renderer::ReverseMethod::None, { pos.X - size_Texture.Width, pos.Y + size_Texture.Height, pos.X, pos.Y }, comment, {1.0,1.0} };
			textures_Border[UPPER_RIGHT] = { texture, Renderer::ReverseMethod::Horizontal, { pos.X + size.Width, pos.Y + size_Texture.Height, pos.X + size.Width + size_Texture.Width, pos.Y }, comment, { 1.0, 1.0 } };
			textures_Border[LOWER_LEFT] = { texture, Renderer::ReverseMethod::Vertical, { pos.X - size_Texture.Width, pos.Y - size.Height, pos.X, pos.Y - size.Height - size_Texture.Height }, comment, { 1.0, 1.0 } };
			textures_Border[LOWER_RIGHT] = { texture, Renderer::ReverseMethod::BothDirection, { pos.X + size.Width, pos.Y - size.Height, pos.X + size.Width + size_Texture.Width, pos.Y - size.Height - size_Texture.Height }, comment, { 1.0, 1.0 } };
			return;
		}
		if (comment & BorderComment::UpperLeft)
			textures_Border[UPPER_LEFT] = { texture, Renderer::ReverseMethod::None, { pos.X - size_Texture.Width, pos.Y - size_Texture.Height, pos.X, pos.Y }, comment, { 1.0, 1.0 } };
		if (comment & BorderComment::UpperRight)
			textures_Border[UPPER_RIGHT] = { texture, Renderer::ReverseMethod::None, { pos.X + size.Width, pos.Y - size_Texture.Height, pos.X + size.Width + size_Texture.Width, pos.Y }, comment, { 1.0, 1.0 } };
		if (comment & BorderComment::LowerLeft)
			textures_Border[LOWER_LEFT] = { texture, Renderer::ReverseMethod::None, { pos.X - size_Texture.Width, pos.Y - size.Height, pos.X, pos.Y - size.Height - size_Texture.Height }, comment, { 1.0, 1.0 } };
		if (comment & BorderComment::LowerRight)
			textures_Border[LOWER_RIGHT] = { texture, Renderer::ReverseMethod::None, { pos.X + size.Width, pos.Y - size.Height, pos.X + size.Width + size_Texture.Width, pos.Y - size.Height - size_Texture.Height }, comment, { 1.0, 1.0 } };
	}
}

void TextBar::BindTexture(TextureRef texture)
{
	Entity::BindTexture(texture);
}

void TextBar::Render()
{
	for (auto &texture : textures_Border)
	{
		if (texture.Texture)
			Renderer::DrawRectangle(texture.Texture->GetIndex(),
				texture.Rect,
				texture.ReverseMethod,
				texture.TextureDuplication);
	}
	TextEntity::Render();
}

void TextBar::Resize()
{
	if (!available || !size.Width || !size.Height)
		return;
	TextEntity::Resize();
	Size size_Control = { (long)((this->size.Width / 100.0) * windowSize->Height), (long)((this->size.Height / 100.0) * windowSize->Height) };
	for (auto &texture : textures_Border)
	{
		if (texture.Texture)
		{
			BindBorderTexture(texture.Texture, texture.Comment);
		}
	}
}

#undef LEFT
#undef TOP
#undef RIGHT
#undef BOTTOM
#undef UPPER_LEFT
#undef UPPER_RIGHT
#undef LOWER_LEFT
#undef LOWER_RIGHT
_L_END