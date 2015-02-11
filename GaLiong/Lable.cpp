#include "Lable.h"

_L_BEGIN
Lable::Lable() : fontSize({ 0, 0 })
{
	implemented = ControlInterface::IRenderable;
}

void Lable::AppendText(const wchar_t *text)
{
	if (!available)
		return;

	this->text.append(text);

	ClearTextures();
	TextureBase *t = font->RenderString(this->text.c_str(), { size.Width * 7.2, size.Height * 7.2 });
	const Size &&s = t->GetSize();
	fontSize = { s.Width / 7.2, s.Height / 7.2 };
	textures.push_back(t);
	empty = false;
}

void Lable::ChangeText(const wchar_t *text)
{
	if (!available)
		return;

	this->text = text;
	if (!this->text.length())
		Clear();

	ClearTextures();
	TextureBase *t = font->RenderString(this->text.c_str(), { size.Width * 7.2, size.Height * 7.2 });
	const Size &&s = t->GetSize();
	fontSize = { s.Width / 7.2, s.Height / 7.2 };
	textures.push_back(t);
	empty = false;
}

void Lable::Render()
{
	if (!visible && !available && empty)
		return;

	for (list<TextureBase *>::iterator it = textures.begin(); it != textures.end(); ++it) // Go to Entity::Render for details.
	{
		if (!(*it) || !(*it)->IsAvailable())
		{
			Renderer::DrawWithoutTexture({ pos.X, pos.Y, pos.X + fontSize.Width, pos.Y - fontSize.Height });
			return;
		}
		// Rendering image upside-down will be much faster processing data in the memory.
		// * NOTE: rendered fonts' image are upside-down in general.
		Renderer::DrawRectangleUpsideDown((*it)->Get().GetIndex(), { pos.X, pos.Y, pos.X + fontSize.Width, pos.Y - fontSize.Height });
	}
}

Lable::~Lable()
{
}
_L_END