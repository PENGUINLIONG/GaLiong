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
	TextureBuilder builder(Texture::PixelFormat::RGBA, Texture::ByteSize::UByte);
	TextureRef texture = font->RenderString(this->text, maximum, &spare);

	if (texture.expired())
		return false;
	//else
		//texture.lock()->Generate(Texture::Filter::Nearest);
	// We can't do the generate staff here since OpenGL does not support multithreading.

	TextureStrongRef ref = texture.lock();
	
	const Size &&s = ref->GetSize();
	fontSize = {
		s.Width * 100.0 / (double)windowSize->Height,
		s.Height * 100.0 / (double)windowSize->Height
	};
	fontPos = { pos.X + ((size.Width - fontSize.Width) / 2), pos.Y - ((size.Height - fontSize.Height) / 2) };

	textures.push_back(ref);
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
			
			Texture *targetPtr = texture.lock().get();
			textures.remove_if([targetPtr](TextureRef &texture){return texture.lock().get() == targetPtr; });
			continue;
		}
		lock_guard<recursive_mutex> lock(texture.lock()->occupy);

		TextureStrongRef sref = texture.lock();
		if (!sref->GetIndex())
			sref->Generate(Texture::Filter::Nearest); // But we can generate here!

		// Rendering image upside-down will be much faster processing data in the memory.
		// * NOTE: rendered fonts' image are upside-down in general.
		switch (alignment)
		{
			case Alignment::Center:
				Renderer::DrawRectangle(texture.lock()->GetIndex(),
				{ fontPos.X, fontPos.Y, fontPos.X + fontSize.Width, fontPos.Y - fontSize.Height },
				Renderer::ReverseMethod::Vertical);
				break;
			case Alignment::Left:
				Renderer::DrawRectangle(texture.lock()->GetIndex(),
				{ pos.X, pos.Y, pos.X + fontSize.Width, pos.Y - fontSize.Height },
				Renderer::ReverseMethod::Vertical);
				break;
		}
	}
}

Label::~Label()
{
}
_L_END