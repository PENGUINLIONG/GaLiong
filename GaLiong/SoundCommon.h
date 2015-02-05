#pragma once
#include "Preprocess.h"

typedef struct {
	WORD Channels; // The number of channels: 1->Mono; 2->Stereo
	DWORD SamplesPerSec;
	DWORD AvgBytesPerSec;
	WORD BlockAlign; // (Length of each block of data)
	WORD BitsPerSample; // (width of PCM sample)
} PCMFormat;