#include "IClickable.hpp"

_L_BEGIN
MouseEventArgs::MouseEventArgs(Point Location) : Location(Location)
{
}

MouseEventArgs::MouseEventArgs(Point Location, MouseButtons Button, bool ButtonDown) : Button(Button), ButtonDown(ButtonDown), Location(Location)
{
}

MouseEventArgs::MouseEventArgs(Point Location, int Delta) : Delta(Delta), Location(Location)
{
}
_L_END