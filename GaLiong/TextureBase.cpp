#include "TextureBase.h"

_L_BEGIN
SizeD TextureBase::CalculateDuplication(Size &container)
{
	Size _size = GetSize();
	return { (double)container.Width / (double)(_size.Width),
		(double)container.Height / (double)(_size.Height) };
}
_L_END