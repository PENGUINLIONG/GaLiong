#pragma once
#include "Preprocess.h"
#include "Texture.h"
#include "Renderer.h"
#include "IClickable.h"
#include "IRenderable.h"

_L_BEGIN
class _L_ Entity : public IRenderable
{
public:
	void IRenderable::Render() override;
	void BindTexture(Texture *texture)
	{
		if (!texture)
			return;
		this->texture = texture;
	}
	virtual void SetPosition(PointD position)
	{
		this->pos = position;
	}
	virtual void SetSize(SizeD size)
	{
		this->size = size;
	}
	virtual void SetAlpha(unsigned char alpha)
	{
		this->alpha = alpha;
	}
	virtual unsigned int GetTag()
	{
		return EntityType::IRenderable;
	}
protected:
	unsigned char alpha = 255;
	Texture *texture = nullptr;
	Renderer renderer;
	PointD pos;
	SizeD size;
};
_L_END
