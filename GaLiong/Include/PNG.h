#pragma once
#include "Preprocess.h"
#include "TextureBase.h"

_L_BEGIN
typedef Byte8 Signature;
template<class T> struct Chunk
{
	Byte4 Length;
	Byte4 ChunkType;
	T ChunkData;
	Byte4 CRC;
};

struct ChunkData_Critical_IHDR
{
	Byte4 Width;
	Byte4 Height;
	Byte1 BitDepth;
	Byte1 ColorDepth;
	Byte1 CompressionMethod;
	Byte1 FilterMethod;
	Byte1 InterlaceMethod;
};
typedef Chunk<struct ChunkData_Critical_IHDR> Chunk_IHDR;
struct ChunkData_Critical_PLTE
{
	struct PaletteRGB
	{
		Byte1 Red;
		Byte1 Green;
		Byte1 Blue;
	} *Colors;
};
typedef Chunk<struct ChunkData_Critical_PLTE> Chunk_PLTE;
struct ChunkData_Critical_IDAT
{
	Buffer Data;
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
	void ToTexture(wchar_t *path, TextureBase *texture, FileReadOption option = FileReadOption::None);
	~PNG();
private:
	ifstream stream;
	static const Byte4 chunkTypeList[4];
};
_L_END