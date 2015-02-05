#include "Character.h"

_L_BEGIN
Character::Character(Renderer &renderer)
{
	this->renderer = renderer;
	visible = true;
}

void Character::Render()
{
	if (!visible)
		return;
	if (!texture || !texture->Index)
	{
		renderer.DrawWithoutTexture({ pos.X, pos.Y, pos.X + size.Width, pos.Y - size.Height });
		return;
	}
	glColor4ub(0xFF, 0xFF, 0xFF, alpha);
	if (this->displayMode == CharacterDisplayMode::Normal)
		renderer.DrawRectangle(texture->Index, { pos.X, pos.Y, pos.X + size.Width, pos.Y - size.Height });
	else
		renderer.DrawRectangleUpsideDown(texture->Index, { pos.X, pos.Y, pos.X + size.Width, pos.Y - size.Height });
	if (fx != CharacterFX::Normal)
		ProcessFX();
}

void Character::SetPosition(PointD position)
{
	Entity::SetPosition(position);
	fxCounter = 0;
	pos_Original = position;
}
void Character::SetSize(SizeD size)
{
	Entity::SetSize(size);
	fxCounter = 0;
	pos = pos_Original;
}
void Character::SwitchDisplayMode(CharacterDisplayMode displayMode)
{
	if (displayMode == CharacterDisplayMode::Inherit)
		return;
	if (displayMode == CharacterDisplayMode::Hidden)
		visible = false;
	else
		visible = true;
	this->displayMode = displayMode;
}
void Character::SwitchFX(CharacterFX fx)
{
	if (fx == CharacterFX::Inherit)
		return;
	this->fx = fx;
	fxCounter = 0;
	pos = pos_Original;
}

void Character::ProcessFX()
{
	switch (fx)
	{
		case CharacterFX::Shaky:
		{
			if (fxCounter >= 360)
			{
				if (fxCounter >= 600)
				{
					fxCounter = 0;
					return;
				}
				if (fxCounter == 360)
					pos = pos_Original;
				fxCounter++;
				return;
			}
			else
				fxCounter += 20;

			pos.X += sin((double)fxCounter) / 10.0f;
			return;
		}
		case CharacterFX::Flowing:
		{
			if (fxCounter >= 250)
			{
				if (fxCounter == 250)
				{
					pos = pos_Original;
					fxCounter = 0;
				}
				return;
			}
			else
				fxCounter++;

			pos.X += sin(fxCounter / 20.0f) / 30.0f;
			size.Width += sin(fxCounter / 20.0f) / 30.0f;
			pos.Y += cos(fxCounter / 10.0f) / 15.0f;
			size.Height += cos(fxCounter / 10.0f) / 15.0f;
			return;
		}
		case CharacterFX::Abnormal:
		{
			switch (fxCounter)
			{
				case 0:
				{
					pos = { pos.X - 0.5f, pos.Y };
					fxCounter++;
					return;
				}
				case 15:
				{
					pos = { pos.X + 0.25f, pos.Y - 0.5f };
					fxCounter++;
					return;
				}
				case 30:
				{
					pos = { pos.X + 0.25f, pos.Y + 0.25f };
					fxCounter++;
					return;
				}
				case 45:
				{
					pos = { pos.X - 0.5f, pos.Y + 0.5f };
					fxCounter++;
					return;
				}
				case 60:
				{
					pos = { pos.X + 0.75, pos.Y + 0.25f };
					fxCounter++;
					return;
				}
				case 75:
				{
					pos = { pos.X + 0.5f, pos.Y - 0.25f };
					fxCounter++;
					return;
				}
				case 90:
				{
					pos = pos_Original;
					fxCounter = 0;
					return;
				}
			}
			fxCounter++;
			return;
		}
		case CharacterFX::ExAbnormal:
		{
			switch (fxCounter)
			{
				case 0:
				{
					pos = { pos.X - 0.5f, pos.Y };
					fxCounter++;
					return;
				}
				case 5:
				{
					pos = { pos.X + 0.25f, pos.Y - 0.5f };
					fxCounter++;
					return;
				}
				case 10:
				{
					pos = { pos.X + 0.25f, pos.Y + 0.25f };
					fxCounter++;
					return;
				}
				case 15:
				{
					pos = { pos.X - 0.5f, pos.Y + 0.5f };
					fxCounter++;
					return;
				}
				case 20:
				{
					pos = { pos.X + 0.75, pos.Y + 0.25f };
					fxCounter++;
					return;
				}
				case 25:
				{
					pos = { pos.X + 0.5f, pos.Y - 0.25f };
					fxCounter++;
					return;
				}
				case 30:
				{
					pos = pos_Original;
					fxCounter = 0;
					return;
				}
			}
			fxCounter++;
			return;
		}
		case CharacterFX::ExExAbnormal:
		{
			switch (fxCounter)
			{
				case 0:
				{
					pos = { pos.X - 0.5f, pos.Y };
					fxCounter++;
					return;
				}
				case 2:
				{
					pos = { pos.X + 0.25f, pos.Y - 0.5f };
					fxCounter++;
					return;
				}
				case 4:
				{
					pos = { pos.X + 0.25f, pos.Y + 0.25f };
					fxCounter++;
					return;
				}
				case 6:
				{
					pos = { pos.X - 0.5f, pos.Y + 0.5f };
					fxCounter++;
					return;
				}
				case 8:
				{
					pos = { pos.X + 0.75, pos.Y + 0.25f };
					fxCounter++;
					return;
				}
				case 10:
				{
					pos = { pos.X + 0.5f, pos.Y - 0.25f };
					fxCounter++;
					return;
				}
				case 12:
				{
					pos = pos_Original;
					fxCounter = 0;
					return;
				}
			}
			fxCounter++;
			return;
		}
	}
}

Character::~Character()
{
}
_L_END