#pragma once
#include "Preprocess.hpp"
#include "TextEntity.hpp"
#include "IClickable.hpp"
#include "Logger.hpp"

_L_BEGIN
class _L_ Button : public TextEntity, public IClickable
{
public:
	Button();
	virtual ~Button() override;
	bool CheckClick(Size window, Point point) override final;
	virtual void BindTexture(TextureRef texture)
	{
		Entity::BindTexture(texture);
	}
	void ClickEventHandler(Point point) override final;
};
_L_END