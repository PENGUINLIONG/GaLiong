#pragma once
#include "Preprocess.h"
#include "TextEntity.h"
#include "IClickable.h"
#include "Logger.h"

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