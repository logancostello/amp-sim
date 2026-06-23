#pragma once
#include <SFML/Graphics.hpp>
#include "Slider.h"
#include "../amp/AmpSettings.h"

class UI {
    public:
        UI(AmpSettings& ampSettings);
        void run();

    private:
        sf::RenderWindow window;
        Slider volumeSlider;
        Slider gainSlider;

        void handleEvents();
        void render();
};