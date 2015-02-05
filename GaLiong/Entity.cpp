#include "Entity.h"

_L_BEGIN
void Entity::Render()
{
	if (!visible)
		return;
	if (!texture || !texture->Index)
	{
		renderer.DrawWithoutTexture({ pos.X, pos.Y, pos.X + size.Width, pos.Y - size.Height });
		return;
	}
	glColor4ub(255, 255, 255, alpha);
	renderer.DrawRectangle(texture->Index, { pos.X, pos.Y, pos.X + size.Width, pos.Y - size.Height });
}
_L_END
