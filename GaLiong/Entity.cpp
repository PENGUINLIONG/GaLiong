#include "Entity.h"

_L_BEGIN
Entity::Entity() : pos({ 0.0f, 0.0f }), size({ 0.0f, 0.0f })
{
}

void Entity::Render()
{
	if (!visible)
		return;

	for (const auto &texture : textures) // The order to render the textures is to
	{
		if (!texture || !texture->IsAvailable())
		{
			Renderer::DrawWithoutTexture({ pos.X, pos.Y, pos.X + size.Width, pos.Y - size.Height });
			return;
		}
		Renderer::DrawRectangle(texture->GetIndex(), { pos.X, pos.Y, pos.X + size.Width, pos.Y - size.Height });
	}
}

Entity::~Entity()
{
	ClearTextures();
}
_L_END