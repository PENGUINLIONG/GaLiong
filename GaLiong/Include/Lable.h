#pragma once
#include "Preprocess.h"
#include "Entity.h"
#include "Renderer.h"
#include "Texture.h"

_L_BEGIN
class _L_ Lable : public Entity
{
public:
	Lable();
	virtual void Render() override final
	{
		if (!visible)
			return;

		for (list<TextureBase *>::iterator it = textures.begin(); it != textures.end(); ++it) // Go to Entity::Render for details.
		{
			if (!(*it) || !(*it)->IsAvailable())
			{
				Renderer::DrawWithoutTexture({ pos.X, pos.Y, pos.X + size.Width, pos.Y - size.Height });
				return;
			}
			// Rendering image upside-down will be much faster processing data in the memory.
			// * NOTE: rendered fonts' image are upside-down in general.
			Renderer::DrawRectangleUpsideDown((*it)->Get().GetIndex(), { pos.X, pos.Y, pos.X + size.Width, pos.Y - size.Height });
		}
	}
	inline virtual void SetPosition(PointD position)
	{
		this->pos = position;
	}
	inline virtual void SetSize(SizeD size)
	{
		this->size = size;
	}
	~Lable();
};
_L_END