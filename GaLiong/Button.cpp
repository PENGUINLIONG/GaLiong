#include "Button.hpp"

_L_BEGIN
Button::Button()
{
	MouseButton += Button_MouseButton;
	MouseHover += [](void *sender, MouseEventArgs e){
		Log << L"Hover!" << EndLog;
	};
}

Button::~Button()
{
}

void Button::Button_MouseButton(void *sender, MouseEventArgs e)
{
	Log << L"Button clicked!" << EndLog;
}
_L_END