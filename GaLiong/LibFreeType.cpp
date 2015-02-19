#include "LibFreeType.h"

_L_BEGIN
LibFreeType::LibFreeType()
{
	// Create a handle to the freetype lib.
	if (FT_Init_FreeType(&library))
		return;
}

Font *LibFreeType::NewFont(wchar_t *path)
{
	Buffer buffer;
	long long length;

	// A UTF-8 hack, the freetype lib does not support UTF-8 originally.
	// But passing a pre-readed data block is available.
	ifstream stream;
	stream.open(path, stream.in | stream.binary | stream._Nocreate);
	if (!stream.is_open())
		return nullptr;

	length = stream.seekg(stream.beg, stream.end).tellg();
	buffer = new unsigned char[length];
	stream.seekg(stream.beg);
	stream.read((char *)buffer, length);
	stream.close();

	faceIndex++;

	Font *font = new Font();

	font->file = buffer;

	FT_New_Memory_Face(library, buffer, length, faceIndex, &font->face);
	FT_Select_Charmap(font->face, FT_ENCODING_UNICODE);
	FT_Stroker_New(library, &font->stroker);

	font->size = { 0, 0 };
	font->fontColor = font->outlineColor = { 0xFF, 0xFF, 0xFF, 0xFF };

	return font;
}

LibFreeType::~LibFreeType()
{
	FT_Done_FreeType(library);
}
_L_END
