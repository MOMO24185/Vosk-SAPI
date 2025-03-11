#include "VoskSAPI.h"
#include "AudioCapture.h"
#include <vosk_api.h>
#include <iostream>
#include <vector>

VoskSAPI::VoskSAPI() {
	// Initializing the recognizer with the model path and sample rate
	VoskModel* model = vosk_model_new("models");
	if (!model) {
		std::cerr << "Failed to load model!" << std::endl;
		return;
	}

	recognizer = vosk_recognizer_new(model, 48000.0f);
	if (!recognizer) {
		std::cerr << "Failed to create recognizer!" << std::endl;
		vosk_model_free(model); // Clean up if creation fails
	}
}

VoskSAPI::~VoskSAPI() {
	if (recognizer) {
		vosk_recognizer_free(recognizer);
	}
}

void VoskSAPI::ProcessAudio(const std::vector<uint8_t>& audioData) {
	if (recognizer) {
		if (vosk_recognizer_accept_waveform(recognizer, (const char*)audioData.data(), audioData.size())) {
			const char* result = vosk_recognizer_result(recognizer);
			std::cout << "Recognized: " << result << std::endl;
		}
	}
}

void VoskSAPI::StartListening() {
	// Starting the audio capture, passing the callback function
	audioCapture.StartCapture([this](const std::vector<uint8_t>& audioData) {
		ProcessAudio(audioData);
	});
}

void VoskSAPI::StopListening() {
	audioCapture.StopCapture();
}
