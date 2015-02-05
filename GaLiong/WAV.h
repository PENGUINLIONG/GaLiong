#pragma once
#include "Preprocess.h"
#include "SoundCommon.h"

_L_BEGIN
typedef struct {
	DWORD RIFF;
	DWORD Length;
	DWORD WAVE;
} RIFFWaveHeaderChunk;

typedef struct {
	DWORD Size;
	WORD FormatTag;
	WORD Channels;
	DWORD SamplesPerSec;
	DWORD AvgBytesPerSec;
	WORD BlockAlign;
	WORD BitsPerSample;
} RIFFWaveFormatChunk;

typedef struct {
	DWORD Size;
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
	bool available;
	unsigned int offset = 0;
	unsigned int endpoint = 0;
	ifstream *stream = nullptr;
	RIFFWaveHeaderChunk header;
	RIFFWaveFormatChunk format;
	RIFFWaveDataChunk data;

	void InitHeader();
};
_L_END