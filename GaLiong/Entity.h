#pragma once
#include "Preprocess.h"
#include "Texture.h"
#include "Renderer.h"
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
	inline void virtual SetPosition(PointD position)
	{
		this->pos = position;
	}
	inline void virtual SetSize(SizeD size)
	{
		this->size = size;
	}
	const inline bool Implemented(unsigned long long key)
	{
		return key & implemented ? true : false;
	}
protected:
	bool visible = true;
	unsigned long long implemented = 0x00;
	list<Texture *> textures;
	PointD pos;
	SizeD size;
};
_L_END