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
	Character(Renderer &renderer);
	void IRenderable::Render() override;
	void SetPosition(PointD position) override;
	void SetSize(SizeD size) override;
	void SwitchDisplayMode(CharacterDisplayMode displayMode);
	void SwitchFX(CharacterFX fx);
	~Character();
private:
	short fxCounter = 0;
	PointD pos_Original;
	CharacterDisplayMode displayMode = CharacterDisplayMode::Normal;
	CharacterFX fx = CharacterFX::Normal;

	void ProcessFX();
};
_L_END
