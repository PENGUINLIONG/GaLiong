#include "WindowsAudioSession.h"

_L_BEGIN

#define SAFE_RELEASE(p) if (p) { p->Release(); p = nullptr; }

WindowsAudioSession::WindowsAudioSession()
{
	available = CoInitialize(NULL) ? false : true;
}

bool WindowsAudioSession::Init(PCMFormat fmt)
{
	if (!available)
		return false;
	// If there is no error has been occured during the execution of fuction, they return S_OK (= HRESULT(0L)).
	// So we can get the right state simply. (As well as the one in the construct function)
	do
	{
		if (CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (void **)&pDeviceEnumerator))
			break;
		if (pDeviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice))
			break;
		if (pDevice->Activate(__uuidof(IAudioClient), CLSCTX_ALL, NULL, (void **)&pAudioClient))
			break;
		if (pAudioClient->GetMixFormat(&pWaveFormatEx))
			break;
		pWaveFormatEx->wFormatTag = WAVE_FORMAT_PCM;
		pWaveFormatEx->nChannels = fmt.Channels;
		pWaveFormatEx->nSamplesPerSec = fmt.SamplesPerSec;
		pWaveFormatEx->nAvgBytesPerSec = fmt.AvgBytesPerSec;
		pWaveFormatEx->nBlockAlign = fmt.BlockAlign;
		pWaveFormatEx->wBitsPerSample = fmt.BitsPerSample;
		if (pAudioClient->IsFormatSupported(AUDCLNT_SHAREMODE_SHARED, pWaveFormatEx, &pWaveFormatEx) == AUDCLNT_E_UNSUPPORTED_FORMAT)
			break;
		if (pAudioClient->Initialize(AUDCLNT_SHAREMODE_SHARED, 0, requestedDuration, 0, pWaveFormatEx, NULL))
			break;
		if (pAudioClient->GetBufferSize(&bufferSize))
			break;
		if (pAudioClient->GetService(__uuidof(IAudioRenderClient), (void **)pAudioRenderClient))
			break;
		available = true;
		return true;
	} while (false);
	// If something goes wrong...
	Dispose();
	return false;
}

void WindowsAudioSession::Dispose()
{
	CoTaskMemFree(pWaveFormatEx);
	SAFE_RELEASE(pDeviceEnumerator);
	SAFE_RELEASE(pDevice);
	SAFE_RELEASE(pAudioClient);
	SAFE_RELEASE(pAudioRenderClient);
}

WindowsAudioSession::~WindowsAudioSession()
{
	available = false;
	Dispose();
	CoUninitialize();
}

#undef SAFE_RELEASE

_L_END