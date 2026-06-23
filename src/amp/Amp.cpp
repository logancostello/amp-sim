#include "Amp.h"
#include <algorithm>

Amp::Amp() {};

float Amp::processInput(float input, AmpSettings* ampSettings) {
    
    float distorted = input;
    for (int i = 0; i < 12; i++) {
        distorted = distorted * ampSettings->gain;
        distorted = std::tanh(distorted);
    }

    float output = distorted * ampSettings->volume;
    return output;
}