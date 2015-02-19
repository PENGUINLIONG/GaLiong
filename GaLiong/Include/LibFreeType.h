#pragma once
#include "Preprocess.h"
#include "Font.h"

_L_BEGIN
class _L_ LibFreeType
{
public:
	LibFreeType();
	Font *NewFont(wchar_t *path);
	~LibFreeType();
#ifdef _INSIDER_COMPILATION
private:
	long faceIndex = 0;
	FT_Library library;
#endif
};
_L_END
