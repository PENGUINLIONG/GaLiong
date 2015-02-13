#include "Label.h"

_L_BEGIN
Label::Label() : fontSize({ 0, 0 }), fontPos({ 0, 0 })
{
	implemented = ControlInterface::IRenderable;
}

bool Label::GenerateFont()
{
	ClearTextures();
	empty = true;

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
	fontPos = { pos.X + ((size.Width - fontSize.Width) / 2), pos.Y - ((size.Height - fontSize.Height) / 2) };

	textures.push_back(t);
	empty = false;

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
			Renderer::DrawWithoutTexture({ fontPos.X, fontPos.Y, fontPos.X + fontSize.Width, fontPos.Y - fontSize.Height });
			return;
		}
		// Rendering image upside-down will be much faster processing data in the memory.
		// * NOTE: rendered fonts' image are upside-down in general.
		Renderer::DrawRectangleUpsideDown((*it)->Get().GetIndex(), { fontPos.X, fontPos.Y, fontPos.X + fontSize.Width, fontPos.Y - fontSize.Height });
	}
}

Label::~Label()
{
}
_L_END