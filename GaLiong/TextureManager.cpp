#include "TextureManager.hpp"

_L_BEGIN
TextureManagerImpl::TextureManagerImpl()
{
}
TextureManagerImpl::~TextureManagerImpl()
{
	for (auto &texture : refs)
	{
		if (texture)
		{
			delete texture.get();
			texture.reset();
		}
	}
}

TextureRef TextureManagerImpl::NewTexture()
{
	TextureStrongRef ref(new Texture(), [](Texture *&texture){});
	refs.push_back(ref);
	return TextureRef(ref);
}
TextureRef TextureManagerImpl::NewTexture(BufferLength dataLength, Buffer data, Size size, Flag pixelFormat, Flag byteSize)
{
	TextureStrongRef ref(new Texture(), [](Texture *&texture){});
	ref->Set(dataLength, data, size, pixelFormat, byteSize);
	refs.push_back(ref);
	return TextureRef(ref);
}
_L_END