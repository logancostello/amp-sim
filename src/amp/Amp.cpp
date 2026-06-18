#include "Amp.h"

Amp::Amp() {};

float Amp::processInput(float input, AmpSettings* ampSettings) {
    return input * ampSettings->volume;
}