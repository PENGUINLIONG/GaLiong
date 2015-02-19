#pragma once
#include "Preprocess.h"

_L_BEGIN
typedef struct {
	Byte2 Channels; // The number of channels: 1->Mono; 2->Stereo
	Byte4 SamplesPerSec;
	Byte4 AvgBytesPerSec;
	Byte2 BlockAlign; // (Length of each block of data)
	Byte2 BitsPerSample; // (width of PCM sample)
} PCMFormat;
_L_END