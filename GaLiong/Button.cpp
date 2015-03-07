#include "Button.hpp"

_L_BEGIN
Button::Button()
{
	implemented = ControlInterface::IRenderable | ControlInterface::IClickable;
}

Button::~Button()
{
}

bool Button::CheckClick(PointD point)
{
	if (point.X < pos.X ||
		point.Y > pos.Y ||
		point.X > pos.X + size.Width ||
		point.Y < pos.Y - size.Height)
		return false;
	
	for (const TextureRef &texture : textures)
	{
		if (texture.expired())
		{
			Texture *targetPtr = texture.lock().get();
			textures.remove_if([targetPtr](TextureRef &texture){ return texture.lock().get() == targetPtr; });
			continue;
		}

		lock_guard<recursive_mutex> lock(texture.lock()->occupy);

		TextureStrongRef ref = texture.lock();
		if (!ref->IsInformative())
			continue;
		if (ref->SameType(Texture::PixelFormat::Ignore))
		{
			if (ref->SameType(Texture::PixelFormat::BGR) ||
				ref->SameType(Texture::PixelFormat::RGB))
				return true;
			else if (ref->SameType(Texture::PixelFormat::RGBA))
			{
				// Calculate the offset to the pixel and check the alpha.
				const Byte pixelLength = ref->GetPixelLength();
				const Size &textureSize = ref->GetSize();

				switch (pixelLength)
				{
					case 4: // Maybe I should optimize this progress?
					{
						Size offset =
						{
							static_cast<long>((point.X - pos.X) / size.Width * textureSize.Width), // X offset.
							-static_cast<long>((point.Y - pos.Y) / size.Height * textureSize.Height) // Y offset
						};
						if (*(ref->GetData() + ((offset.Width + (textureSize.Height - offset.Height) * textureSize.Width) << 2) + 3))
							return true;
						break;
					}
					// Be compatible with 16-bit depth pixel later.

					//case 8:
					//	if (*reinterpret_cast<Byte2 *>(ref->GetData() + ((point.X - x0) + (point.Y - y0) * ref->GetSize().Width) * pixelLength + 6))
					//		return true;
					default:
						break;
				}
			}
		}
	}
	return false;
}

void Button::ClickEventHandler(Point point)
{
	Log << L"Button clicked!" << EndLog;
}
_L_END