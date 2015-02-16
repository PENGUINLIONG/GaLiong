#include "TextureBuffer.h"

_L_BEGIN
TextureBuffer::TextureBuffer()
{
	max = 8;
	current = textures = new Texture[8];
	last = textures + 7 * sizeof(Texture *);
	append = textures;
	available = true;
}
TextureBuffer::TextureBuffer(unsigned char length)
{
	if (!length)
		return;
	max = length;
	current = textures = new Texture[length];
	last = textures + (length - 1) * sizeof(Texture *);
	append = textures;
	available = true;
}

TextureBuffer &TextureBuffer::MoveFor(unsigned char steps)
{
	if (!available)
		return *this;

	while (steps >= max)
		steps -= max;
	while (steps)
	{
		if (current == last)
		{
			current = textures;
			return MoveFor(steps - 1);
		}
		current += sizeof(Texture *);
	}
	return *this;
}

void TextureBuffer::Append(Texture *source) //Incompleted
{
	if (append == last)
		append = textures;
	else
		append += sizeof(Texture *);
	*append = *source;
}

TextureBuffer::~TextureBuffer()
{
	if (textures)
		delete [] textures;
}
_L_END
