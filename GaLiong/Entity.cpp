#include "Entity.h"

_L_BEGIN
Entity::Entity() : pos({ 0.0f, 0.0f }), size({ 0.0f, 0.0f })
{
}

void Entity::Render()
{
	if (!visible)
		return;

	for (list<TextureBase *>::iterator it = textures.begin(); it != textures.end(); ++it) // The order to render the textures is to
	{
		if (!(*it) || !(*it)->IsAvailable())
		{
			Renderer::DrawWithoutTexture({ pos.X, pos.Y, pos.X + size.Width, pos.Y - size.Height });
			return;
		}
		Renderer::DrawRectangle((*it)->Get().GetIndex(), { pos.X, pos.Y, pos.X + size.Width, pos.Y - size.Height });
	}
}

Entity::~Entity()
{
	ClearTextures();
}
_L_END