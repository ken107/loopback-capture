#pragma once
#include <windef.h>

class MyAudioSink {
private:
	int bytesPerFrame;

public:
	HRESULT SetFormat(WAVEFORMATEX *pwfx);
	HRESULT CopyData(BYTE *pData, UINT32 numFramesAvailable, BOOL *bDone);
};
