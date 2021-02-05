#include <Windows.h>
#include <mmeapi.h>
#include "MyAudioSink.h"

MyAudioSink::MyAudioSink(FILE *stream) {
	this->stream = stream;
}

HRESULT MyAudioSink::SetFormat(WAVEFORMATEX *pwfx) {
	bytesPerFrame = pwfx->nChannels * pwfx->wBitsPerSample / 8;
	return S_OK;
}

HRESULT MyAudioSink::CopyData(BYTE *pData, UINT32 numFramesAvailable) {
	if (pData == NULL) {
		size_t bytesRemaining = numFramesAvailable * bytesPerFrame;
		while (bytesRemaining > 0) {
			size_t bytesToWrite = min(bytesRemaining, sizeof(silence));
			size_t bytesWritten = fwrite(silence, 1, bytesToWrite, stream);
			if (bytesWritten != bytesToWrite) return ferror(stream);
			bytesRemaining -= bytesWritten;
		}
		return S_OK;
	}
	else {
		size_t framesWritten = fwrite(pData, bytesPerFrame, numFramesAvailable, stream);
		return framesWritten != numFramesAvailable ? ferror(stream) : S_OK;
	}
}

HRESULT MyAudioSink::Flush() {
	int result = fflush(stream);
	return result != 0 ? ferror(stream) : S_OK;
}
