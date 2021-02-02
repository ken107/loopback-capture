#include <Windows.h>
#include <mmeapi.h>
#include <stdio.h>
#include "MyAudioSink.h"

HRESULT MyAudioSink::SetFormat(WAVEFORMATEX *pwfx) {
	bytesPerFrame = pwfx->nChannels * pwfx->wBitsPerSample / 8;
	return S_OK;
}

HRESULT MyAudioSink::CopyData(BYTE *pData, UINT32 numFramesAvailable) {
	if (pData == NULL) {
		size_t bytesRemaining = numFramesAvailable * bytesPerFrame;
		while (bytesRemaining > 0) {
			size_t bytesToWrite = min(bytesRemaining, sizeof(silence));
			size_t bytesWritten = fwrite(silence, 1, bytesToWrite, stdout);
			if (bytesWritten != bytesToWrite) return ferror(stdout);
			bytesRemaining -= bytesWritten;
		}
		return S_OK;
	}
	else {
		size_t framesWritten = fwrite(pData, bytesPerFrame, numFramesAvailable, stdout);
		return framesWritten != numFramesAvailable ? ferror(stdout) : S_OK;
	}
}
