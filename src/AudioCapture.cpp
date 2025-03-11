#include "AudioCapture.h"
#include <iostream>
#include <thread>
#include <vector>

AudioCapture::AudioCapture() : pDevice(nullptr), pAudioClient(nullptr), pCaptureClient(nullptr), capturing(false) {
	CoInitialize(nullptr);
}

AudioCapture::~AudioCapture() {
	StopCapture();
	CoUninitialize();
}

bool AudioCapture::StartCapture(std::function<void(const std::vector<uint8_t>&)> callback) {
	audioCallback = callback;
	capturing = true;

	IMMDeviceEnumerator* pEnumerator = nullptr;
	HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL,
								  __uuidof(IMMDeviceEnumerator), (void**)&pEnumerator);
	if (FAILED(hr)) return false;

	hr = pEnumerator->GetDefaultAudioEndpoint(eCapture, eConsole, &pDevice);
	pEnumerator->Release();
	if (FAILED(hr)) return false;

	hr = pDevice->Activate(__uuidof(IAudioClient), CLSCTX_ALL, nullptr, (void**)&pAudioClient);
	if (FAILED(hr)) return false;

	WAVEFORMATEX* pwfx;
	hr = pAudioClient->GetMixFormat(&pwfx);
	if (FAILED(hr)) return false;

	hr = pAudioClient->Initialize(AUDCLNT_SHAREMODE_SHARED, 0, 10000000, 0, pwfx, nullptr);
	if (FAILED(hr)) return false;

	hr = pAudioClient->GetService(__uuidof(IAudioCaptureClient), (void**)&pCaptureClient);
	if (FAILED(hr)) return false;

	pAudioClient->Start();

	std::thread([this]() { CaptureLoop(); }).detach();

	return true;
}

void AudioCapture::StopCapture() {
	capturing = false;
	if (pAudioClient) pAudioClient->Stop();
}

void AudioCapture::CaptureLoop() {
	while (capturing) {
		UINT32 packetLength = 0;
		pCaptureClient->GetNextPacketSize(&packetLength);

		while (packetLength != 0) {
			BYTE* pData;
			UINT32 numFramesAvailable;
			DWORD flags;
			pCaptureClient->GetBuffer(&pData, &numFramesAvailable, &flags, nullptr, nullptr);

			std::vector<uint8_t> buffer(pData, pData + numFramesAvailable * 2);
			audioCallback(buffer);

			pCaptureClient->ReleaseBuffer(numFramesAvailable);
			pCaptureClient->GetNextPacketSize(&packetLength);
		}

		Sleep(10);
	}
}
