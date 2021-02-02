#pragma once
#include <windows.h>

class MyAudioSink;

HRESULT GetMixFormat(WAVEFORMATEX &wfx);
HRESULT RecordAudioStream(MyAudioSink *pMySink, BOOL &bDone);
