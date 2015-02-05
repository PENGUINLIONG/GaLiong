#include "TextureBuffer.h"

_L_BEGIN
TextureBuffer::TextureBuffer()
{
	offset = 7;
	last = textures + 7 * sizeof(Texture *);
	textures = new Texture[8];
	available = true;
}
TextureBuffer::TextureBuffer(unsigned char length)
{
	if (!length)
		return;
	offset = length - 1;
	current = textures = new Texture[length];
	last = textures + offset * sizeof(Texture *);
	available = true;
}

TextureBuffer *TextureBuffer::MoveNext(unsigned char &flag)
{
	if (available)
	{
		if (current == last)
			current = textures;
		else
			current += sizeof(Texture *);
		if (!current->GetAvailability() && flag < offset)
			MoveNext(++flag);
	}
	return this;
}

void TextureBuffer::Append(Texture *source) //Incompleted
{
	if (append == last)
		append = textures;
	else
		append += sizeof(Texture *);
	*append = std::move(*source);
}

TextureBuffer::~TextureBuffer()
{
	if (textures)
		delete [] textures;
}
_L_END