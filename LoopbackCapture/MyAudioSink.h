#pragma once
#include <windef.h>

class MyAudioSink {
private:
	WORD bytesPerFrame;
	BYTE silence[16000] = {};

public:
	HRESULT SetFormat(WAVEFORMATEX *pwfx);
	HRESULT CopyData(BYTE *pData, UINT32 numFramesAvailable);
};
