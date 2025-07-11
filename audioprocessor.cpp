#include "audioprocessor.h"
#include <cstring>

AudioProcessor::AudioProcessor(RtAudio *audio, uint inDeviceId, uint outDeviceId)
    : audio(audio)
{
    iParams.deviceId = inDeviceId;
    iParams.nChannels = 2;
    iParams.firstChannel = 0;

    oParams.deviceId = outDeviceId;
    oParams.nChannels = 2;
    oParams.firstChannel = 0;

    unsigned jackRate = audio->getDeviceInfo(inDeviceId).preferredSampleRate;
    sampleRate = jackRate;
}

AudioProcessor::AudioProcessor(RtAudio *audio)
    : AudioProcessor(audio, audio->getDefaultInputDevice(), audio->getDefaultOutputDevice())
{
}

AudioProcessor::~AudioProcessor()
{
    stop();
}

int AudioProcessor::passThrough(void *outputBuffer, void *inputBuffer, unsigned int nFrames, double streamTime, RtAudioStreamStatus status, void *userData)
{
    std::memcpy(outputBuffer, inputBuffer, nFrames * sizeof(double) * 2); // 2 channels
    return 0;
}

void AudioProcessor::start()
{
    if (audio->isStreamOpen()) return;
    audio->openStream(
        &oParams,
        &iParams,
        RTAUDIO_FLOAT64,
        sampleRate,
        &bufferFrames,
        &AudioProcessor::passThrough
    );
    audio->startStream();
}

void AudioProcessor::stop()
{
    if (audio->isStreamRunning()) audio->stopStream();
    if (audio->isStreamOpen()) audio->closeStream();
}

void AudioProcessor::setDevices(uint inDeviceId, uint outDeviceId)
{
    stop();

    iParams.deviceId = inDeviceId;
    oParams.deviceId = outDeviceId;

    sampleRate = audio->getDeviceInfo(inDeviceId).preferredSampleRate;

    start();
}
