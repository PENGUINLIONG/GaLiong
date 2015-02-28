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
	Size maximum = {
		size.Width * (double)windowSize->Height * 0.01, // You can try using windowSize->Width instead of windowSize->Height.
		size.Height * (double)windowSize->Height * 0.01
	};
	Size spare = { 0, 0 };
	TextureRef t = font->RenderString(this->text.c_str(), maximum, &spare);

	if (!t)
		return false;
	
	const Size &&s = t->GetSize();
	fontSize = {
		s.Width * 100.0 / (double)windowSize->Height,
		s.Height * 100.0 / (double)windowSize->Height
	};
	fontPos = { pos.X + ((size.Width - fontSize.Width) / 2), pos.Y - ((size.Height - fontSize.Height) / 2) };

	textures.push_back(TextureRef(t));
	empty = false;

	return true;
}

void Label::Render()
{
	if (!visible && !available && empty)
		return;

	for (const auto &texture : textures) // Go to Entity::Render for details.
	{
		if (texture.expired())
		{
			Renderer::DrawWithoutTexture({ fontPos.X, fontPos.Y, fontPos.X + fontSize.Width, fontPos.Y - fontSize.Height });
			return;
		}
		else
			textures.remove(texture);
		// Rendering image upside-down will be much faster processing data in the memory.
		// * NOTE: rendered fonts' image are upside-down in general.
		Renderer::DrawRectangle(texture->GetIndex(),
			{ fontPos.X, fontPos.Y, fontPos.X + fontSize.Width, fontPos.Y - fontSize.Height },
			Renderer::ReverseMethod::Vertical);
	}
}

Label::~Label()
{
}
_L_END