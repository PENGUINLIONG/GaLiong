#include "Button.h"

#pragma warning( disable: 4244 )

_L_BEGIN
Button::Button(Renderer &renderer)
{
	this->renderer = renderer;
	available = true;
}

bool Button::CheckClick(Size window, Point point)
{
	if (!available)
		return false;
	cout << "Check click... At (" << point.X << ", " << point.Y << ")." << endl;

	int &&x0 = window.Width * (pos.X + 50.0f) / 100,              &&y0 = window.Height * (50.0f - pos.Y) / 100,
		&&x1 = window.Width * (pos.X + size.Width + 50.0f) / 100, &&y1 = window.Height * (50.0f - pos.Y + size.Height) / 100;

	if (x0 > point.X || point.X > x1 || y0 > point.Y || point.Y > y1)
		return false;
	if (texture->PixelFormat == GL_BGR_EXT || texture->PixelFormat == GL_RGB)
		return true;
	else if (texture->PixelFormat == GL_BGRA_EXT || texture->PixelFormat == GL_RGBA)
	{
		int pixelLength = texture->GetPixelLength();
		if (pixelLength < 5)
		{
			if (*(unsigned char *)(texture->Data + ((point.X - x0) + (point.Y - y0) * texture->Size.Width) * pixelLength + 3)) // Calculate the offset to the pixel.
				return true;
		}
		else
		{
			if (*(unsigned short *)(texture->Data + ((point.X - x0) + (point.Y - y0) * texture->Size.Width) * pixelLength + 6))
				return true;
		}
	}
	else if (texture->PixelFormat == GL_ALPHA)
	{
		if (*(unsigned char *)(texture->Data + ((point.X - x0) + (point.Y - y0) * texture->Size.Width)))
			return true;
	}
	return false;
}

void Button::ClickEventHandler(Point point)
{
	cout << "Button clicked!" << endl;
}

Button::~Button()
{
}
_L_END