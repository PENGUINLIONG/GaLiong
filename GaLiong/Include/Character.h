#pragma once
#include "cmath"
#include "Preprocess.h"
#include "Entity.h"

_L_BEGIN
class _L_ Character : public Entity
{
public:
enum class DisplayMode {
	Inherit = 0,
	Hidden = 1,
	Normal = 2,
	UpsideDown = 3
};
enum class FX {
		Inherit = 0,
		Normal = 1,
		Shaky = 2,
		Flowing = 3,
		Abnormal = 4,
		ExAbnormal = 5,
		ExExAbnormal = 6 //////////////////////Need Implementation/////////////////////
		// Accessory
		/*Intimate,
		Joyful,
		Jetting,*/
	};

	Character();
	virtual ~Character() override;
	virtual void Render() override;
	virtual void SetPosition(PointD position) override
	{
		Entity::SetPosition(position);
		fxCounter = 0;
		pos_Original = position;
	}
	virtual void SetSize(SizeD size) override
	{
		Entity::SetSize(size);
		fxCounter = 0;
		pos = pos_Original;
	}
	void SwitchDisplayMode(DisplayMode displayMode)
	{
		if (displayMode == DisplayMode::Inherit)
			return;
		if (displayMode == DisplayMode::Hidden)
			visible = false;
		else
			visible = true;
		this->displayMode = displayMode;
	}
	void SwitchFX(FX fx)
	{
		if (fx == FX::Inherit)
			return;
		this->fx = fx;
		fxCounter = 0;
		pos = pos_Original;
	}
private:
	short fxCounter = 0;
	PointD pos_Original;
	DisplayMode displayMode = DisplayMode::Normal;
	FX fx = FX::Normal;

	void ProcessFX();
};
_L_END
