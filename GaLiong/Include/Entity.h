#pragma once
#include "Preprocess.h"
#include "Control.h"
#include "Renderer.h"
#include "Texture.h"
#include "IRenderable.h"

_L_BEGIN
class _L_ Entity : public Control, public IRenderable
{
public:
	Entity();
	virtual void Render() override;
	inline void BindTexture(TextureBase *texture)
	{
		if (!texture || !texture->IsAvailable())
			return;
		textures.push_back(texture);
	}
	virtual inline void SetPosition(PointD position)
	{
		this->pos = position;
	}
	virtual inline void SetSize(SizeD size)
	{
		this->size = size;
	}
protected:
	inline void ClearTextures()
	{
		if (!textures.size())
			return;
		for_each(textures.begin(), textures.end(), [](TextureBase *&texture)
		{
			delete texture;
		});
		textures.clear();
	}
	~Entity();
protected:
	bool visible = true;
	list<TextureBase *> textures;
	PointD pos;
	SizeD size;
};
_L_END