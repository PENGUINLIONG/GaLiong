#include "PNG.h"

_L_BEGIN
PNG::PNG()
{
	//                                 IHDR        PLTE        IDAT        IEND
	const DWORD32 chunkTypeList[4] = { 0x52444849, 0x45547680, 0x54414449, 0x444E4549 };
}
PNG::~PNG()
{
}

void PNG::ToTexture(wchar_t *path, TextureBase *texture, FileReadOption option)
{
	if (stream.is_open())
		stream.close();
	stream.open(path, stream.in | stream.binary | stream._Nocreate);
	Signature s = 0;
	stream.read((char *)s, 8);
	if (s != 0x0A1A0A0D474E5089)
		return;

	unsigned int size = 0;
	unsigned int chunkType = 0;
	Chunk_IHDR ihdr;
	Chunk_PLTE plte;
	Chunk_IDAT idat;
	Chunk_IEND iend;

	while (!stream.eof())
	{
		stream.read((char *)&size, 4);
		stream.read((char *)&chunkType, 4);
		
		switch (chunkType)
		{
			case 0x52444849: // IHDR
				stream.read((char *)&ihdr.ChunkData, sizeof(ChunkData_Critical_IHDR));
				if (ihdr.ChunkData.BitDepth != 8)
					return;
				if (ihdr.ChunkData.ColorDepth != 2);
					// ... (as BMP)
				else if (ihdr.ChunkData.ColorDepth != 6)
					// ... 
				
				break;
			default:
				break;
		}
	}

}

_L_END