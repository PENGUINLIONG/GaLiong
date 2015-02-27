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
		if (!texture->IsInformative())
			continue;
		if (texture->SameType(TextureBase::PixelFormat::BGR, TextureBase::ByteSize::UByte) ||
			texture->SameType(TextureBase::PixelFormat::RGB, TextureBase::ByteSize::UByte))
			return true;
		else if (texture->SameType(TextureBase::PixelFormat::RGBA, TextureBase::ByteSize::UByte))
		{
			int pixelLength = texture->GetPixelLength();
			if (pixelLength < 5)
			{
				if (*(Buffer)(texture->GetData() + ((point.X - x0) + (point.Y - y0) * texture->GetSize().Width) * pixelLength + 3)) // Calculate the offset to the pixel.
					return true;
			}
			else
			{
				if (*(unsigned short *)(texture->GetData() + ((point.X - x0) + (point.Y - y0) * texture->GetSize().Width) * pixelLength + 6))
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