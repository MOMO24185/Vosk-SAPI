#ifndef AUDIO_CAPTURE_H
#define AUDIO_CAPTURE_H

#include <windows.h>
#include <mmdeviceapi.h>
#include <audioclient.h>
#include <vector>
#include <functional>

class AudioCapture {
public:
	AudioCapture();
	~AudioCapture();

	bool StartCapture(std::function<void(const std::vector<uint8_t>&)> callback);
	void StopCapture();

private:
	IMMDevice* pDevice;
	IAudioClient* pAudioClient;
	IAudioCaptureClient* pCaptureClient;
	std::function<void(const std::vector<uint8_t>&)> audioCallback;
	bool capturing;

	void CaptureLoop();
};

#endif
