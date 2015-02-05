/*
 __________________________________________________________________________________________
|                               _     ____   _      _____  _        ___                    |
|                   |      |   / \   |    \ | \   |   |   | \   |  /                       |
|                   |      |  /___\  |____/ |  \  |   |   |  \  | |                        |
|                   |  /\  | |     | |   \  |   \ |   |   |   \ | |  ___                   |
|                    \/  \/  |     | |    \ |    \| __|__ |    \|  \___|                   |
|                                                                                          |
|----------------------------- This module may make you blind.------------------------------|
|                                                                                          |
|The code here are working well but it's not good for you to read them without sunglasses. |
|Reading the code might make you *BLIND*. Please think over seriously before you decide to.|
|__________________________________________________________________________________________|
*/
#include "TextureBuilder.h"

_L_BEGIN
TextureBuilder::TextureBuilder(WORD pixelFormat, WORD byteSize)
{
	this->boundary = { MAXLONG, MINLONG, MINLONG, MAXLONG };
	this->pixelFormat = pixelFormat;
	this->byteSize = byteSize;
	if (!(pxLength = Texture::GetPixelLength(pixelFormat, byteSize)))
		throw exception("Unsupported pixel format.");
}

bool TextureBuilder::AppendConponent(TextureConponent conponent)
{
	if (conponent.Texture->PixelFormat != pixelFormat || conponent.Texture->ByteSize != byteSize ||
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
	if (!textures.size())
		return nullptr;

	long dstOffset = 0, srcOffset = 0;
	Size size = { boundary.Right - boundary.Left, boundary.Top - boundary.Bottom };
	long length = size.Width * size.Height * pxLength;

	unsigned char *buffer = new unsigned char[length];
	memset(buffer, 0, length); // Prevent the black background appearing.

	// Copy the value of each pixel.
	for (vector<TextureConponent>::iterator it = textures.begin(); it != textures.end(); it++) // Copy pixels here.
	{
		TextureConponent &ref = *it;
		if (!ref.Texture)
			continue;

		dstOffset = ((boundary.Top - ref.Rect.Top) * size.Width + (ref.Rect.Left - boundary.Left)) * pxLength;
		srcOffset = 0;

		int nextLine = (size.Width - ref.Texture->Size.Width) * pxLength;
		int x, y;

		for (y = 0; y < ref.Texture->Size.Height; y++)
		{
			for (x = 0; x < ref.Texture->Size.Width * pxLength; x++)
			{
#ifdef _DEBUG
				if (y == 0 || y == ref.Texture->Size.Height - 1 || x < 4 || x > ref.Texture->Size.Width * pxLength - 5)
					*(buffer + dstOffset) = 0xFF;
				else
#endif
				if (*(ref.Texture->Data + srcOffset))
					*(buffer + dstOffset) = *(ref.Texture->Data + srcOffset); // Do copy from source to destination.

				dstOffset++;
				srcOffset++;
			}
			dstOffset += nextLine;
		}
#ifdef _DEBUG
		dstOffset = 0;
		for (y = 0; y < size.Height; y++)
		{
			for (x = 0; x < size.Width * pxLength; x++)
			{
				if (y == 0 || y == size.Height - 1 || x < 4 || x > size.Width * pxLength - 5)
					*(buffer + dstOffset) = 0xFF;
				dstOffset++;
			}
		}
#endif
		continue;
	}



	// Ending.
	Texture *texture = new Texture();
	texture->DataLength = length;
	texture->Data = buffer;
	texture->Size = size;
	texture->PixelFormat = pixelFormat;
	texture->ByteSize = byteSize;
	texture->Generate();
	texture->Informative = true;

	return texture;
}

TextureBuilder::~TextureBuilder()
{
	for (vector<TextureConponent>::iterator it = textures.begin(); it != textures.end(); it++) // it == Texture **
	{
		if (it->Texture)
		{
			delete it->Texture;
			it->Texture = nullptr;
		}
	}
}
_L_END