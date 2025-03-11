#ifndef VOSK_SAPI_H
#define VOSK_SAPI_H

#include "AudioCapture.h"
#include <vosk_api.h>
#include <vector>

class VoskSAPI {
public:
	VoskSAPI();
	~VoskSAPI();

	void StartListening();
	void StopListening();

private:
	VoskRecognizer* recognizer;
	VoskModel* model;
	AudioCapture audioCapture;

	void ProcessAudio(const std::vector<uint8_t>& audioData);
};

#endif // VOSK_SAPI_H
