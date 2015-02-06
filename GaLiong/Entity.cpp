#include "Entity.h"

_L_BEGIN
void Entity::Render()
{
	if (!visible)
		return;

	for (list<Texture *>::iterator it = textures.begin(); it != textures.end(); it++) // The order to render the textures is to
	{
		if (!(*it) || !(*it)->Index)
		{
			Renderer::DrawWithoutTexture({ pos.X, pos.Y, pos.X + size.Width, pos.Y - size.Height });
			return;
		}
		glColor4ub(255, 255, 255, alpha);
		Renderer::DrawRectangle((*it)->Index, { pos.X, pos.Y, pos.X + size.Width, pos.Y - size.Height });
	}
}
_L_END