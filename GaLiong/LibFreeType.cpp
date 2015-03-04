#include "LibFreeType.hpp"

_L_BEGIN
LibFreeType::LibFreeType()
{
	// Create a handle to the freetype lib.
	FT_Init_FreeType(reinterpret_cast<FT_Library *>(&library));
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
	buffer = new Byte[length];
	stream.seekg(stream.beg);
	stream.read((char *)buffer, length);
	stream.close();

	faceIndex++;

	Font *font = new Font();

	font->file = buffer;

	FT_New_Memory_Face(reinterpret_cast<FT_Library>(library), buffer, length, faceIndex, &font->face);
	FT_Select_Charmap(font->face, FT_ENCODING_UNICODE);
	FT_Stroker_New(reinterpret_cast<FT_Library>(library), &font->stroker);

	font->size = { 0, 0 };
	font->fontColor = font->outlineColor = { 0xFF, 0xFF, 0xFF, 0xFF };

	return font;
}

LibFreeType::~LibFreeType()
{
	FT_Done_FreeType(reinterpret_cast<FT_Library>(library));
}
_L_END