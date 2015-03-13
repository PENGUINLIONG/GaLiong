#include "TextEntity.hpp"

_L_BEGIN
TextEntity::TextEntity()
{
	Render += TextEntity_Render;
	Resize += TextEntity_Resize;
}

TextEntity::~TextEntity()
{
}
_L_END