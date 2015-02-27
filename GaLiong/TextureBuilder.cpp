#include "TextureBuilder.h"

_L_BEGIN
TextureBuilder::TextureBuilder(TextureBase::PixelFormat pixelFormat, TextureBase::ByteSize byteSize) : boundary({ MAXLONG, MINLONG, MINLONG, MAXLONG }), pixelFormat(pixelFormat), byteSize(byteSize)
{
	if (!(pxLength = Texture::GetPixelLength(pixelFormat, byteSize)))
		throw exception("Unsupported pixel format.");
}

bool TextureBuilder::AppendConponent(TextureComponent component)
{
	if (!component.Texture->IsInformative() || !component.Texture->SameType(pixelFormat, byteSize) ||
		component.Rect.Right <= component.Rect.Left || component.Rect.Top <= component.Rect.Bottom)
		return false;
	
	if (component.Rect.Left < boundary.Left)
		boundary.Left = component.Rect.Left;
	if (component.Rect.Top > boundary.Top)
		boundary.Top = component.Rect.Top;
	if (component.Rect.Right > boundary.Right)
		boundary.Right = component.Rect.Right;
	if (component.Rect.Bottom < boundary.Bottom)
		boundary.Bottom = component.Rect.Bottom;

	textures.push_back({ component.Rect, component.Texture });
	return true;
}

void TextureBuilder::Make(TextureRef &target)
{
	if (textures.empty())
		return;

	Size size = { boundary.Right - boundary.Left, boundary.Top - boundary.Bottom };
	long length = size.Width * size.Height * pxLength;

	Buffer buffer = new Byte[length];
	memset(buffer, 0, length); // Prevent the black background appearing.

	int x, y;

	// Copy the value of each pixel.
	for (vector<TextureComponent>::iterator it = textures.begin(); it != textures.end(); ++it) // Copy pixels here.
	{
		TextureComponent &ref = *it;
		const Buffer textureData = ref.Texture->GetData();
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
	target = TextureRef(new Texture());
	target->Set(length, buffer, size, pixelFormat, byteSize);
}

TextureBuilder::~TextureBuilder()
{
	Log << L"TextureBuilder destructed." << EndLog;
}
_L_END