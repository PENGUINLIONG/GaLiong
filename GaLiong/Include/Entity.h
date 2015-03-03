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
	void BindTexture(TextureRef texture);
	void ClearTextures();
	virtual void Render() override;
	virtual void Resize() override {}
	virtual void SetPosition(PointD position);
	virtual void SetSize(SizeD size)
	{
		this->size = size;
	}
protected:
	bool visible = true;
	list<TextureRef> textures;
	PointD pos;
	SizeD size;
};
_L_END