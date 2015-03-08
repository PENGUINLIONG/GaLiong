#include "WAV.hpp"

_L_BEGIN
WAV::WAV()
{
	data.Data = nullptr;
}

void WAV::InitHeader()
{
	Byte4 tag;
	offset = 12;

	stream.read((char *)&header, sizeof(RIFFWaveHeaderChunk));
	if (header.RIFF != 0x46464952 || header.WAVE != 0x45564157) // 'RIFF' 'WAVE'
		return;

	stream.read((char *)&tag, sizeof(Byte4));
	if (tag == 0x20746D66) // 'fmt '
	{
		format.Size = 0;
		stream.read((char *)&format, sizeof(RIFFWaveFormatChunk));
		if (format.Size > 16)
			stream.seekg(format.Size - 16, stream.cur);
		offset += format.Size + 8;
	}
	else return;

	stream.read((char *)&tag, sizeof(Byte4));
	if (tag == 0x74636166) // 'fact'
	{
		Byte4 size;
		stream.read((char *)&size, sizeof(Byte4));
		stream.seekg(size, stream.cur);
		stream.read((char *)&tag, sizeof(Byte4));
		offset += size + 12;
	}

	if (tag == 0x61746164) // 'data'
	{
		stream.read((char *)&data, sizeof(Byte4));
		offset += 8;
	}
	else return;

	if (data.Data == nullptr)
		data.Data = new char[data.Size];

	available = true;
}

void WAV::ReadData(wchar_t *path)
{
	Dispose();
	if (stream.is_open())
		stream.close();
	stream.open(path, stream.binary | stream._Nocreate);

	InitHeader();
	stream.seekg(offset, stream.beg);
	stream.read(data.Data, data.Size);
	
	offset = 0;
	endpoint = data.Size;
	available = true;
}

void WAV::SelectFromTo(unsigned int offsetTime, unsigned int duration)
{
	if (duration == 0)
	{
		endpoint = data.Size;
		return;
	}
	offset = (format.BitsPerSample * format.SamplesPerSec * format.Channels * offsetTime) >> 3;
	
	endpoint = offset + ((format.BitsPerSample * format.SamplesPerSec * format.Channels * duration) >> 3);
	if (endpoint > data.Size)
		endpoint = data.Size;
}

void WAV::Dispose()
{
	delete [] data.Data;
	available = false;
}

char *WAV::GetSelected()
{
	if (available)
		return data.Data + offset;
	else return nullptr;
}

unsigned int WAV::GetSelectedLength()
{
	return endpoint - offset;
}

PCMFormat WAV::GetPCMFormat()
{
	return{ format.Channels, format.SamplesPerSec, format.AvgBytesPerSec, format.BlockAlign, format.BitsPerSample };
}

WAV::~WAV()
{
	Dispose();
}
_L_END
