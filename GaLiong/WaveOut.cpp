#include "WaveOut.h"

_L_BEGIN
WaveOut::WaveOut()
{
}

void WaveOut::Init(PCMFormat fmt)
{
	waveFormatEx.cbSize = 0;
	waveFormatEx.wFormatTag = WAVE_FORMAT_PCM;
	waveFormatEx.nChannels = fmt.Channels;
	waveFormatEx.nSamplesPerSec = fmt.SamplesPerSec;
	waveFormatEx.nAvgBytesPerSec = fmt.AvgBytesPerSec;
	waveFormatEx.nBlockAlign = fmt.BlockAlign;
	waveFormatEx.wBitsPerSample = fmt.BitsPerSample;

	waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveFormatEx, (DWORD_PTR)Callback, (DWORD_PTR)this, CALLBACK_FUNCTION);
}

void WaveOut::Write(Buffer buffer, BufferLength bufferLength, PCMFormat fmt, bool loop)
{
	Init(fmt);
	if (playing)
		Reset();
	waveHDR.lpData = reinterpret_cast<LPSTR>(buffer);
	waveHDR.dwBufferLength = bufferLength;
	waveHDR.dwFlags = 0;
	waveOutPrepareHeader(hWaveOut, &waveHDR, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &waveHDR, sizeof(WAVEHDR));
	playing = true;
	this->loop = loop;
}
void WaveOut::Write(Buffer buffer, BufferLength bufferLength, PCMFormat fmt)
{
	Write(buffer, bufferLength, fmt, true);
}
void WaveOut::Write()
{
	waveOutPrepareHeader(hWaveOut, &waveHDR, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &waveHDR, sizeof(WAVEHDR));
	playing = true;
}

void WaveOut::Reset()
{
	playing = false;
	waveOutReset(hWaveOut);
	waveOutBreakLoop(hWaveOut);
	waveOutUnprepareHeader(hWaveOut, &waveHDR, sizeof(WAVEHDR));
}

void WaveOut::Pause()
{
	waveOutPause(hWaveOut);
	playing = false;
}

void WaveOut::Restart()
{
	waveOutRestart(hWaveOut);
	playing = true;
}

void WaveOut::Callback(HWAVEOUT hWaveOut, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
	WaveOut *instance = reinterpret_cast<WaveOut *>(dwInstance);
	if (uMsg == WOM_DONE && instance->playing && instance->loop)
		instance->Write();
}

WaveOut::~WaveOut()
{
	Reset();
	waveOutClose(hWaveOut);
}
_L_END