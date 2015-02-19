#pragma once
#include "Preprocess.h"
#include "SoundCommon.h"

_L_BEGIN
typedef struct {
	Byte4 RIFF;
	Byte4 Length;
	Byte4 WAVE;
} RIFFWaveHeaderChunk;

typedef struct {
	Byte4 Size;
	Byte2 FormatTag;
	Byte2 Channels;
	Byte4 SamplesPerSec;
	Byte4 AvgBytesPerSec;
	Byte2 BlockAlign;
	Byte2 BitsPerSample;
} RIFFWaveFormatChunk;

typedef struct {
	Byte4 Size;
	char *Data;
} RIFFWaveDataChunk;

class _L_ WAV
{
public:
	WAV(ifstream *stream);
	void ReadData(wchar_t *path);
	void SelectFromTo(unsigned int offset, unsigned int duration);
	void Dispose();
	char *GetSelected();
	unsigned int GetSelectedLength();
	PCMFormat GetPCMFormat();
	~WAV();
private:
	bool available = false;
	unsigned int offset = 0;
	unsigned int endpoint = 0;
	ifstream *stream = nullptr;
	RIFFWaveHeaderChunk header;
	RIFFWaveFormatChunk format;
	RIFFWaveDataChunk data;

	void InitHeader();
};
_L_END
