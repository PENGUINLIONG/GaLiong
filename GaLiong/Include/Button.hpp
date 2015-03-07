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
	virtual bool CheckClick(PointD point) override;
	virtual void BindTexture(TextureRef texture)
	{
		Entity::BindTexture(texture);
	}
	virtual void ClickEventHandler(Point point) override;
};
_L_END