#pragma once
#include "Preprocess.h"
#include "ControlBase.h"
#include "Renderer.h"
#include "Texture.h"
#include "IRenderable.h"

_L_BEGIN
class _L_ Entity : public ControlBase, public IRenderable
{
public:
	Entity();
	virtual ~Entity() override;
	void BindTexture(TextureBase *texture)
	{
		if (!texture || !texture->IsAvailable())
			return;
		textures.push_back(texture);
	}
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
	virtual void Render() override;
	virtual void Resize() override {}
	virtual void SetPosition(PointD position)
	{
		this->pos = position;
	}
	virtual void SetSize(SizeD size)
	{
		this->size = size;
	}
protected:
	bool visible = true;
	vector<TextureBase *> textures;
	PointD pos;
	SizeD size;
};
_L_END