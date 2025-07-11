#ifndef AUDIOPROCESSOR_H
#define AUDIOPROCESSOR_H

#include <rtaudio/RtAudio.h>

class AudioProcessor
{
public:
    AudioProcessor(RtAudio *audio);
    AudioProcessor(RtAudio *audio, uint inDeviceId, uint outDeviceId);
    ~AudioProcessor();

    void start();
    void stop();

    void setDevices(uint inDeviceId, uint outDeviceId);

private:
    RtAudio *audio;
    RtAudio::StreamParameters iParams, oParams;

    unsigned sampleRate = 44100;
    unsigned bufferFrames = 256;

    static int passThrough(void *outputBuffer, void *inputBuffer,
                           uint nFrames, double streamTime,
                           RtAudioStreamStatus status, void *userData);
};

#endif // AUDIOPROCESSOR_H
