#pragma once
#include <windef.h>
#include <stdio.h>

class MyAudioSink {
private:
	FILE *stream;
	WORD bytesPerFrame;
	BYTE silence[16000] = {};

public:
	MyAudioSink(FILE *stream);
	HRESULT SetFormat(WAVEFORMATEX *pwfx);
	HRESULT CopyData(BYTE *pData, UINT32 numFramesAvailable);
	HRESULT Flush();
};
