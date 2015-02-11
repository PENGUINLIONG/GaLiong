#include "Label.h"

_L_BEGIN
Label::Label() : fontSize({ 0, 0 })
{
	implemented = ControlInterface::IRenderable;
}

bool Label::AppendText(const wchar_t *text)
{
	if (!available || !wcslen(text))
		return false;
	
	this->text.append(text);

	ClearTextures();
	TextureBase *t = font->RenderString(this->text.c_str(), {
		size.Width * (double)windowSize->Height * 0.01,
		size.Height * (double)windowSize->Height * 0.01
	});

	if (!t)
		return false;

	const Size &&s = t->GetSize();
	fontSize = {
		(double)s.Width * 100.0 / (double)windowSize->Height,
		(double)s.Height * 100.0 / (double)windowSize->Height
	};
	textures.push_back(t);
	empty = false;

	return true;
}

bool Label::ChangeText(const wchar_t *text)
{
	if (!available)
		return false;

	Clear();
	AppendText(text);
	return true;
}

void Label::Render()
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

Label::~Label()
{
}
_L_END