#pragma once
#include "Preprocess.h"
#include "TextureBase.h"

_L_BEGIN
typedef DWORDLONG Signature;
template<class T> struct Chunk
{
	DWORD Length;
	DWORD ChunkType;
	T ChunkData;
	DWORD CRC;
};

struct ChunkData_Critical_IHDR
{
	DWORD Width;
	DWORD Height;
	BYTE BitDepth;
	BYTE ColorDepth;
	BYTE CompressionMethod;
	BYTE FilterMethod;
	BYTE InterlaceMethod;
};
typedef Chunk<struct ChunkData_Critical_IHDR> Chunk_IHDR;
struct ChunkData_Critical_PLTE
{
	struct PaletteRGB
	{
		BYTE Red;
		BYTE Green;
		BYTE Blue;
	} *Colors;
};
typedef Chunk<struct ChunkData_Critical_PLTE> Chunk_PLTE;
struct ChunkData_Critical_IDAT
{
	unsigned char *Data;
};
typedef Chunk<struct ChunkData_Critical_IDAT> Chunk_IDAT;
struct ChunkData_Critical_IEND
{
};
typedef Chunk<ChunkData_Critical_IEND> Chunk_IEND;

class _L_ PNG
{
public:
	PNG();
	unsigned char *ReadChunk(unsigned long length);
	void ToTexture(wchar_t *path, TextureBase &texture, FileReadOption option = FileReadOption::None);
	~PNG();
private:
	ifstream stream;
	static const DWORD chunkTypeList[4];
};
_L_END