#include "Button.h"

_L_BEGIN
Button::Button()
{
	implemented = ControlInterface::IRenderable | ControlInterface::IClickable;
}

Button::~Button()
{
}

bool Button::CheckClick(Size window, Point point)
{
	int x0 = window.Width * (pos.X + 50.0f) / 100.0, y0 = window.Height * (50.0f - pos.Y) / 100.0,
		x1 = window.Width * (pos.X + size.Width + 50.0f) / 100.0, y1 = window.Height * (50.0f - pos.Y + size.Height) / 100.0;

	if (x0 > point.X || point.X > x1 || y0 > point.Y || point.Y > y1)
		return false;

	for (const auto &texture : textures)
	{
		if (texture.expired())
		{
			Texture *targetPtr = texture.lock().get();
			textures.remove_if([targetPtr](TextureRef &texture){return texture.lock().get() == targetPtr; });
			continue;
		}
		TextureStrongRef ref = texture.lock();
		if (!ref->IsInformative())
			continue;
		if (ref->SameType(Texture::PixelFormat::BGR, Texture::ByteSize::UByte) ||
			ref->SameType(Texture::PixelFormat::RGB, Texture::ByteSize::UByte))
			return true;
		else if (ref->SameType(Texture::PixelFormat::RGBA, Texture::ByteSize::UByte))
		{
			int pixelLength = ref->GetPixelLength();
			if (pixelLength < 5)
			{
				if (*reinterpret_cast<Buffer>(ref->GetData() + ((point.X - x0) + (point.Y - y0) * ref->GetSize().Width) * pixelLength + 3)) // Calculate the offset to the pixel.
					return true;
			}
			else
			{
				if (*reinterpret_cast<Byte2 *>(ref->GetData() + ((point.X - x0) + (point.Y - y0) * ref->GetSize().Width) * pixelLength + 6))
					return true;
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