#include "Entity.h"

_L_BEGIN
void Entity::Render()
{
	if (!visible)
		return;

	for (list<Texture *>::iterator it = textures.begin(); it != textures.end(); it++) // The order to render the textures is to
	{
		if (!(*it) || !(*it)->IsAvailable())
		{
			Renderer::DrawWithoutTexture({ pos.X, pos.Y, pos.X + size.Width, pos.Y - size.Height });
			return;
		}
		Renderer::DrawRectangle((*it)->GetIndex(), { pos.X, pos.Y, pos.X + size.Width, pos.Y - size.Height });
	}
}
_L_END