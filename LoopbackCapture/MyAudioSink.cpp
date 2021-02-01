#include <Windows.h>
#include <mmeapi.h>
#include <stdio.h>
#include "MyAudioSink.h"

HRESULT MyAudioSink::SetFormat(WAVEFORMATEX *pwfx) {
	bytesPerFrame = pwfx->nChannels * pwfx->wBitsPerSample / 8;
	return 0;
}

HRESULT MyAudioSink::CopyData(BYTE *pData, UINT32 numFramesAvailable, BOOL *bDone) {
	int count = fwrite(pData, bytesPerFrame, numFramesAvailable, stdout);
	return count != numFramesAvailable ? 3 : 0;
}
