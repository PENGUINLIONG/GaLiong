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
		textures.push_back(texture);
	}
	//void RemoveTexture();
	void inline virtual SetPosition(PointD position)
	{
		this->pos = position;
	}
	void inline virtual SetSize(SizeD size)
	{
		this->size = size;
	}
	void inline virtual SetAlpha(unsigned char alpha)
	{
		this->alpha = alpha;
	}
	const inline bool Implemented(unsigned long long key)
	{
		return key & implemented ? true : false;
	}
protected:
	bool visible = true;
	unsigned long long implemented = 0;
	unsigned char alpha = 255;
	list<Texture *> textures;
	PointD pos;
	SizeD size;
};
_L_END