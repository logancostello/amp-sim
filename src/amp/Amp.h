#pragma once
#include "../amp/AmpSettings.h"

class Amp {
    public:
        Amp();    
        float processInput(float input, AmpSettings* ampSettings);
};