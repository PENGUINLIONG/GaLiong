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

	for (list<TextureBase *>::iterator it = textures.begin(); it != textures.end(); ++it)
	{
		if (!(*it)->IsInformative())
			continue;
		if ((*it)->SameType(GL_BGR_EXT, GL_UNSIGNED_BYTE) || (*it)->SameType(GL_RGB, GL_UNSIGNED_BYTE))
			return true;
		else if ((*it)->SameType(GL_RGBA, GL_UNSIGNED_BYTE))
		{
			int pixelLength = (*it)->GetPixelLength();
			if (pixelLength < 5)
			{
				if (*(unsigned char *)((*it)->GetData() + ((point.X - x0) + (point.Y - y0) * (*it)->GetSize().Width) * pixelLength + 3)) // Calculate the offset to the pixel.
					return true;
			}
			else
			{
				if (*(unsigned short *)((*it)->GetData() + ((point.X - x0) + (point.Y - y0) * (*it)->GetSize().Width) * pixelLength + 6))
					return true;
			}
		}
	}
	return false;
}

void Button::ClickEventHandler(Point point)
{
	cout << "Button clicked!" << endl;
}
_L_END