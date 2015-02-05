#pragma once
#include "Preprocess.h"
#include "Font.h"

_L_BEGIN
class _L_ FreeType
{
public:
	FreeType();
	Font *NewFont(wchar_t *path);
	~FreeType();

	long faceIndex = 0;
	FT_Library library;
};
_L_END