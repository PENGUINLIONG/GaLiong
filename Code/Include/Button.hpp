#pragma once
#include "Preprocess.hpp"
#include "TextEntity.hpp"
#include "IClickable.hpp"
#include "Logger.hpp"

_L_BEGIN
class _L_ Button : public TextEntity
{
public:
	Button();
	virtual ~Button() override;
	virtual bool IsHover(PointD point) override;
	virtual void BindTexture(TextureRef texture)
	{
		Entity::BindTexture(texture);
	}
private:
	bool _MouseHovered = false;
	void Button_MouseButton(void *sender, MouseEventArgs e);
};
_L_END