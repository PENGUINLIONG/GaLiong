/*   __________________________________________________________________________________________
	|                               _     ____   _      _____  _        ___                    |
	|                   |      |   / \   |    \ | \   |   |   | \   |  /                       |
	|                   |      |  /___\  |____/ |  \  |   |   |  \  | |                        |
	|                   |  /\  | |     | |   \  |   \ |   |   |   \ | |  ___                   |
	|                    \/  \/  |     | |    \ |    \| __|__ |    \|  \___|                   |
	|                                                                                          |
	|-----------------------------This module is still developing.-----------------------------|
	|                                                                                          |
	|There could be some incomplete parts(functions/struct/class) and(or) some compiler errors.|
	|Using this module could be *UNSAFE*. Please think over seriously before you decide to use.|
	|__________________________________________________________________________________________|
*/
/*
#pragma once
#include "Preprocess.hpp"
#include <Audioclient.hpp>
#include <audiopolicy.hpp>
#include <Mmdeviceapi.hpp>
#include "SoundCommon.hpp"

#pragma comment(lib, "winmm.lib")

_L_BEGIN
class _L_ WindowsAudioSession
{
public:
	WindowsAudioSession();
	bool Init(PCMFormat pcmFormat);
	void Buffer();
	~WindowsAudioSession();
private:
	bool available = false;
	Buffer buffer;
	unsigned int bufferSize = 0;
	REFERENCE_TIME requestedDuration = 10000000;
	IMMDeviceEnumerator *pDeviceEnumerator = nullptr;
	IMMDevice *pDevice = nullptr;
	IAudioClient *pAudioClient = nullptr;
	IAudioRenderClient *pAudioRenderClient = nullptr;
	WAVEFORMATEX *pWaveFormatEx = nullptr;

	void Dispose();
};
_L_END
*/