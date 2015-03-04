#pragma once
#include "Preprocess.hpp"
#include "ControlBase.hpp"
#include "Renderer.hpp"
#include "Texture.hpp"
#include "IRenderable.hpp"

_L_BEGIN
class _L_ Entity : public ControlBase, public IRenderable
{
public:
	struct BorderComment
	{
		const static Flag NoComment = 0x0000;
		const static Flag Left = 0x0001;
		const static Flag Top = 0x0002;
		const static Flag Right = 0x0004;
		const static Flag Bottom = 0x0008;
		const static Flag UpperLeft = 0x0010;
		const static Flag UpperRight = 0x0040;
		const static Flag LowerLeft = 0x0020;
		const static Flag LowerRight = 0x0080;

		const static Flag EveryBorder = 0x000F;
		const static Flag EveryCorner = 0x00F0;
		const static Flag EveryWhere = 0x00FF;
	};

	class BorderImpl : public ControlBase, public IRenderable
	{
	public:
		// LNK2019 occured when I did not use to add the virtual keyword.
		// That's interesting.
		// If there is someone can tell me what caused that, 
		//     please create an issue on this repo via Github or send an email to admin@penguinliong.moe.
		// Much appriciated!
		virtual void BindTexture(TextureRef texture, const Flag comment);
		virtual void Render() override final;
		virtual void Resize() override final;
	private:
		struct BorderComponent
		{
			TextureRef Texture;
			Renderer::ReverseMethod ReverseMethod;
			RectD Rect;
			Flag Comment;
			SizeD TextureDuplication;
		};
		array<BorderComponent, 8> textures;
		PointD &pos;
		SizeD &size;

		BorderImpl();
		BorderImpl(PointD &pos, SizeD &size);
		virtual ~BorderImpl() override final;
		
		friend class array<BorderComponent, 8>;
		friend class Entity;
	} Border;

	Entity();
	virtual ~Entity() override;

	void BindTexture(TextureRef texture);
	void ClearTextures();
	virtual void Render() override;
	virtual void Resize() override;
	virtual void SetPosition(PointD position);
	virtual void SetSize(SizeD size)
	{
		this->size = size;
	}
	virtual void SetWindowSize(Size *windowSize);
protected:
	bool visible = true;
	list<TextureRef> textures;
	PointD pos;
	SizeD size;
};
_L_END