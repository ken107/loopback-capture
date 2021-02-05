#define no_init_all deprecated

#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <thread>
#include "Capture.h"
#include "MyAudioSink.h"

void adminThread(BOOL &bDone) {
	getchar();
	bDone = true;
}

int main(int argc, char *argv[])
{
	HRESULT hr;
	CoInitialize(nullptr);

	if (argc == 2) {
		if (strcmp(argv[1], "get-mix-format") == 0) {
			WAVEFORMATEX wfx;
			hr = GetMixFormat(wfx);
			if FAILED(hr) goto Exit;

			std::cout << wfx.nSamplesPerSec << "," << wfx.nChannels << std::endl;
		}
		else if (strcmp(argv[1], "record") == 0) {
			_setmode(_fileno(stdout), O_BINARY);

			MyAudioSink sink(stdout);
			BOOL bDone = FALSE;
			std::thread admin(adminThread, std::ref(bDone));
			hr = RecordAudioStream(&sink, bDone);
			admin.join();
			if FAILED(hr) goto Exit;
		}
		else {
			std::cerr << "Bad command" << std::endl;
			hr = 1;
		}
	}
	else {
		std::cout << "Usage:  " << argv[0] << " COMMAND" << std::endl;
		std::cout << std::endl;
		std::cout << "Capture output of the default audio output device" << std::endl;
		std::cout << std::endl;
		std::cout << "Commands:" << std::endl;
		std::cout << "  get-mix-format    Get the nSamplesPerSec and nChannels" << std::endl;
		std::cout << "  record            Start capture to stdout" << std::endl;
		hr = 0;
	}

Exit:
	return hr;
}
