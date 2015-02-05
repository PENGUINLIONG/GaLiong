#include "FreeType.h"

_L_BEGIN
FreeType::FreeType()
{
	// Create a handle to the freetype lib.
	if (FT_Init_FreeType(&library))
		return;
}

Font *FreeType::NewFont(wchar_t *path)
{
	unsigned char *buffer;
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

	return new Font(buffer, length, faceIndex, library);
}

FreeType::~FreeType()
{
	FT_Done_FreeType(library);
}
_L_END