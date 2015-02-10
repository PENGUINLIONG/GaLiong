#include "Lable.h"

_L_BEGIN
Lable::Lable()
{
	Entity::Entity();
	implemented = ControlInterface::IRenderable;
}

Lable::~Lable()
{
}
_L_END