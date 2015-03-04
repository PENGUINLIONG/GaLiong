#pragma once
#include "Preprocess.hpp"
#include "SoundCommon.hpp"

_L_BEGIN
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

	struct RIFFWaveHeaderChunk
	{
		Byte4 RIFF;
		Byte4 Length;
		Byte4 WAVE;
	} header;
	struct RIFFWaveFormatChunk
	{
		Byte4 Size;
		Byte2 FormatTag;
		Byte2 Channels;
		Byte4 SamplesPerSec;
		Byte4 AvgBytesPerSec;
		Byte2 BlockAlign;
		Byte2 BitsPerSample;
	} format;
	struct RIFFWaveDataChunk
	{
		Byte4 Size;
		char *Data;
	} data;

	void InitHeader();
};
_L_END