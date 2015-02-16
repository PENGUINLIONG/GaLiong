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
	virtual void Resize() override {}
	void BindTexture(TextureBase *texture)
	{
		if (!texture || !texture->IsAvailable())
			return;
		textures.push_back(texture);
	}
	virtual void SetPosition(PointD position)
	{
		this->pos = position;
	}
	virtual void SetSize(SizeD size)
	{
		this->size = size;
	}
protected:
	void ClearTextures()
	{
		if (textures.empty())
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
