#pragma once
#include "Preprocess.h"
#include "Entity.h"
#include "IClickable.h"
#include "Renderer.h"

_L_BEGIN
class _L_ Button : public Entity, public IClickable
{
public:
	Button(Renderer &renderer);
	bool IClickable::CheckClick(Size window, Point point) override final;
	void IClickable::ClickEventHandler(Point point) override final;
	unsigned int GetTag() override final
	{
		return EntityType::IClickable | EntityType::IRenderable;
	}
	~Button();
private:
	bool available = false;
};
_L_END
