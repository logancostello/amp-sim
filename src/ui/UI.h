#pragma once
#include <SFML/Graphics.hpp>
#include "Slider.h"


class UI {
    public:
        UI();
        void run();

    private:
        sf::RenderWindow window;
        Slider volumeSlider = Slider();

        void handleEvents();
        void render();
};