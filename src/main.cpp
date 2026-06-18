#include <RtAudio.h>
#include <iostream>
#include <cstdlib>
#include "ui/UI.h"
#include "amp/AmpSettings.h"
#include "amp/Amp.h"

struct CallbackData {
    Amp* amp;
    AmpSettings* ampSettings;
};

int audioCallback(
    void* outputBuffer, 
    void* inputBuffer, 
    unsigned int nFrames, 
    double /*streamTime*/, 
    RtAudioStreamStatus /*status*/, 
    void* userData
)
{
    float* in = static_cast<float*>(inputBuffer);
    float* out = static_cast<float*>(outputBuffer);

    CallbackData* data = static_cast<CallbackData*>(userData);
    AmpSettings* ampSettings = data->ampSettings;
    Amp* amp = data->amp;

    for (unsigned int i = 0; i < nFrames; i++) {
        float ampOutput = amp->processInput(in[i], ampSettings);
        out[i * 2] = ampOutput;
        out[i * 2 + 1] = ampOutput;
    }

    return 0;
}

int main() {
    RtAudio audio;
    Amp amp;
    AmpSettings ampSettings;

    if (audio.getDeviceCount() < 1) {
        std::cerr << "No audio devices found.\n";
        return 1;
    }

    std::vector<unsigned int> ids = audio.getDeviceIds();
    unsigned int inputId = 0, outputId = 0;
    for (unsigned int id : ids) {
        RtAudio::DeviceInfo info = audio.getDeviceInfo(id);
        if (inputId == 0 && info.inputChannels > 0) inputId  = id;
        if (outputId == 0 && info.outputChannels > 0) outputId = id;
    }
    std::cout << "Input: " << audio.getDeviceInfo(inputId).name  << "\n";
    std::cout << "Output: " << audio.getDeviceInfo(outputId).name << "\n";

    RtAudio::StreamParameters inParams, outParams;
    inParams.deviceId = inputId;
    inParams.nChannels = 1;
    outParams.deviceId = outputId;
    outParams.nChannels = 2;

    unsigned int sampleRate = 48000;
    unsigned int bufferFrames = 256;

    CallbackData callbackData { &amp, &ampSettings };

    try {
        audio.openStream(
            &outParams, 
            &inParams, 
            RTAUDIO_FLOAT32, 
            sampleRate, 
            &bufferFrames, 
            &audioCallback, 
            &callbackData
        );
        audio.startStream();
    } catch (std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    UI ui(ampSettings);
    ui.run();

    audio.stopStream();
    audio.closeStream();
    return 0;
}