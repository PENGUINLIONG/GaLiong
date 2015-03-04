#pragma once
#include "Preprocess.hpp"
#include "Font.hpp"

_L_BEGIN
class _L_ LibFreeType
{
public:
	LibFreeType();
	Font *NewFont(wchar_t *path);
	~LibFreeType();
private:
	long faceIndex = 0;
	/*FT_Library*/void *library;
};
_L_END