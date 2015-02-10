#pragma once
#include "Preprocess.h"
#include "SoundCommon.h"

_L_BEGIN
class _L_ WaveOut
{
public:
	WaveOut();
	inline void Write(char *buffer, unsigned int bufferLength, PCMFormat fmt, bool loop);
	inline void Write(char *buffer, unsigned int bufferLength, PCMFormat fmt);
	inline void Reset();
	inline void Pause();
	inline void Restart();
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