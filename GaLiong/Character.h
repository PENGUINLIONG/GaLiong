#pragma once
#include <math.h>
#include "Preprocess.h"
#include "Entity.h"

_L_BEGIN
enum class CharacterDisplayMode {
	Inherit = 0,
	Hidden = 1,
	Normal = 2,
	UpsideDown = 3
};

enum class CharacterFX {
	Inherit = 0,
	Normal = 1,
	Shaky = 2,
	Flowing = 3,
	Abnormal = 4,
	ExAbnormal = 5,
	ExExAbnormal = 6 //////////////////////Need Implementation.//////////////////////
	// Accessory
	/*Intimate,
	Joyful,
	Jetting,*/
};

class _L_ Character : public Entity
{
public:
	Character();
	void IRenderable::Render() override;
	void inline SetPosition(PointD position) override
	{
		Entity::SetPosition(position);
		fxCounter = 0;
		pos_Original = position;
	}
	void inline SetSize(SizeD size) override
	{
		Entity::SetSize(size);
		fxCounter = 0;
		pos = pos_Original;
	}
	void inline SwitchDisplayMode(CharacterDisplayMode displayMode)
	{
		if (displayMode == CharacterDisplayMode::Inherit)
			return;
		if (displayMode == CharacterDisplayMode::Hidden)
			visible = false;
		else
			visible = true;
		this->displayMode = displayMode;
	}
	void inline SwitchFX(CharacterFX fx)
	{
		if (fx == CharacterFX::Inherit)
			return;
		this->fx = fx;
		fxCounter = 0;
		pos = pos_Original;
	}
	~Character();
private:
	short fxCounter = 0;
	PointD pos_Original;
	CharacterDisplayMode displayMode = CharacterDisplayMode::Normal;
	CharacterFX fx = CharacterFX::Normal;

	void ProcessFX();
};
_L_END
