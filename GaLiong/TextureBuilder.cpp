#include "TextureBuilder.h"

_L_BEGIN
TextureBuilder::TextureBuilder(WORD pixelFormat, WORD byteSize) : boundary({ MAXLONG, MINLONG, MINLONG, MAXLONG }),pixelFormat(pixelFormat),byteSize(byteSize)
{
	if (!(pxLength = Texture::GetPixelLength(pixelFormat, byteSize)))
		throw exception("Unsupported pixel format.");
}

bool TextureBuilder::AppendConponent(TextureConponent conponent)
{
	if (!conponent.Texture->IsInformative() || !conponent.Texture->SameType(pixelFormat, byteSize) ||
		conponent.Rect.Right <= conponent.Rect.Left || conponent.Rect.Top <= conponent.Rect.Bottom)
		return false;
	
	if (conponent.Rect.Left < boundary.Left)
		boundary.Left = conponent.Rect.Left;
	if (conponent.Rect.Top > boundary.Top)
		boundary.Top = conponent.Rect.Top;
	if (conponent.Rect.Right > boundary.Right)
		boundary.Right = conponent.Rect.Right;
	if (conponent.Rect.Bottom < boundary.Bottom)
		boundary.Bottom = conponent.Rect.Bottom;

	textures.push_back(conponent);
	return true;
}

Texture *TextureBuilder::Make()
{
	if (textures.empty())
		return nullptr;

	Size size = { boundary.Right - boundary.Left, boundary.Top - boundary.Bottom };
	long length = size.Width * size.Height * pxLength;

	unsigned char *buffer = new unsigned char[length];
	memset(buffer, 0, length); // Prevent the black background appearing.

	int x, y;

	// Copy the value of each pixel.
	for (list<TextureConponent>::iterator it = textures.begin(); it != textures.end(); ++it) // Copy pixels here.
	{
		TextureConponent &ref = *it;
		const unsigned char *textureData = ref.Texture->GetData();
		const Size textureSize = ref.Texture->GetSize();
		
		long dstOffset = ((boundary.Top - ref.Rect.Top) * size.Width + (ref.Rect.Left - boundary.Left)) * pxLength;
		long srcOffset = 0;

		int nextLine = (size.Width - textureSize.Width) * pxLength;


		for (y = 0; y < textureSize.Height; y++)
		{
			for (x = 0; x < textureSize.Width * pxLength; x++)
			{
#ifdef _DEBUG
				if (y == 0 || y == textureSize.Height - 1 || x < 4 || x > textureSize.Width * pxLength - 5)
					*(buffer + dstOffset) = 0xFF;
				else
#endif
				if (*(textureData + srcOffset))
					*(buffer + dstOffset) = *(textureData + srcOffset); // Do copy from source to destination.

				dstOffset++;
				srcOffset++;
			}
			dstOffset += nextLine;
		}
		continue;
	}
#ifdef _DEBUG
	long dstOffset = 0;
	for (y = 0; y < size.Height; y++)
	{
		for (x = 0; x < size.Width * pxLength; x++)
		{
			if (y == 0 || y == size.Height - 1 || x < pxLength || x > (size.Width - 1) * pxLength - 1)
				*(buffer + dstOffset) = 0xFF;
			dstOffset++;
		}
	}
#endif
	
	// Ending.
	Texture *texture = new Texture();
	texture->Set(length, buffer, size, pixelFormat, byteSize);
	texture->Generate();

	return texture;
}

TextureBuilder::~TextureBuilder()
{
	for (list<TextureConponent>::iterator it = textures.begin(); it != textures.end(); ++it) // it == Texture **
	{
		if (it->Texture)
		{
			delete it->Texture;
			it->Texture = nullptr;
		}
	}
}
_L_END