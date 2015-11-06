#pragma once
#include "Preprocess.hpp"
#include "SoundCommon.hpp"

_L_BEGIN
class _L_ WaveOut
{
public:
	WaveOut();
	void Write(Buffer buffer, BufferLength bufferLength, PCMFormat fmt, bool loop);
	void Write(Buffer buffer, BufferLength bufferLength, PCMFormat fmt);
	void Reset();
	void Pause();
	void Restart();
	static void CALLBACK Callback(HWAVEOUT hWaveOut, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);
	~WaveOut();
private:
	bool loop = true;
	bool playing = false;
	char *buffer = nullptr;
	unsigned int bufferLength = 0;
	WAVEFORMATEX waveFormatEx;
	HWAVEOUT hWaveOut;
	WAVEHDR waveHDR;

	void Init(PCMFormat fmt);
	void Write();
};
_L_END