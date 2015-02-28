#include "TextureManager.h"

_L_BEGIN
TextureManagerImpl::TextureManagerImpl()
{
}
TextureManagerImpl::~TextureManagerImpl()
{
}

void TextureManagerImpl::DeleteTexture(TextureRef target)
{
	if (target.expired())
		return;
	Texture *targetPtr = target.lock().get();
	refs.remove_if([targetPtr](const TextureStrongRef &texture){return texture.get() == targetPtr; });
}

TextureRef TextureManagerImpl::NewTexture()
{
	TextureStrongRef ref(new Texture());
	refs.push_back(ref);
	return TextureRef(ref);
}
TextureRef TextureManagerImpl::NewTexture(BufferLength dataLength, Buffer data, Size size, Flag pixelFormat, Flag byteSize)
{
	TextureStrongRef ref(new Texture());
	ref->Set(dataLength, data, size, pixelFormat, byteSize);
	refs.push_back(ref);
	return TextureRef(ref);
}
_L_END