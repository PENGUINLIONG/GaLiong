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
		if (texture.expired())
		{
			Renderer::DrawWithoutTexture({ pos.X, pos.Y, pos.X + size.Width, pos.Y - size.Height });
			
			Texture *targetPtr = texture.lock().get();
			textures.remove_if([targetPtr](TextureRef &texture){return texture.lock().get() == targetPtr; });
			continue;
		}
		Renderer::DrawRectangle(texture.lock()->GetIndex(), { pos.X, pos.Y, pos.X + size.Width, pos.Y - size.Height });
	}
}

Entity::~Entity()
{
	ClearTextures();
}
_L_END