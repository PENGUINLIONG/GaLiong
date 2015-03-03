#include "Entity.h"

_L_BEGIN
Entity::Entity() : pos({ 0.0f, 0.0f }), size({ 0.0f, 0.0f })
{
}

void Entity::BindTexture(TextureRef texture)
{
	if (texture.expired() || !texture.lock()->GetIndex())
		return;
	textures.push_back(texture);
}

void Entity::ClearTextures()
{
	if (textures.empty())
		return;
	textures.clear();
}

void Entity::SetPosition(PointD position)
{
	pos = position;
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
		lock_guard<recursive_mutex> lock(texture.lock()->occupy);
		
		Renderer::DrawRectangle(texture.lock()->GetIndex(), { pos.X, pos.Y, pos.X + size.Width, pos.Y - size.Height });
	}
}

Entity::~Entity()
{
	ClearTextures();
}
_L_END