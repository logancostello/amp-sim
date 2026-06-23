#include "Amp.h"
#include <algorithm>

Amp::Amp() {};

float Amp::processInput(float input, AmpSettings* ampSettings) {
    
    float distorted = input * ampSettings->gain;
    distorted = std::tanh(distorted);

    distorted = input * ampSettings->gain;
    distorted = std::tanh(distorted);

    distorted = input * ampSettings->gain;
    distorted = std::tanh(distorted);

    float output = distorted * ampSettings->volume;
    return output;
}