#include "UI.h"
#include <iostream>

UI::UI() : window(sf::VideoMode::getDesktopMode(), "amp-sim", sf::State::Fullscreen)
{
    window.setFramerateLimit(60);

    float w = window.getSize().x;
    float h = window.getSize().y;

    sf::Font font;
    if (!font.openFromFile("/System/Library/Fonts/Monaco.ttf")) {
        std::cerr << "Failed to load font\n";
        return;
    }
    font.setSmooth(true);

    volumeSlider = Slider(sf::Vector2f(w * 0.5f, h * 0.5), "Volume", font, 0.5);
}

void UI::run() {
    while (window.isOpen()) {
        handleEvents();
        render();
    }
}

void UI::handleEvents() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            window.close();

        volumeSlider.handleEvent(*event, window);
    }
}

void UI::render() {
    window.clear(sf::Color(20, 20, 20));

    volumeSlider.draw(window);

    window.display();
}