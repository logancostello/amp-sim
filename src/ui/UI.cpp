#include "UI.h"
#include <iostream>

UI::UI(AmpSettings& ampSettings) : window(sf::VideoMode::getDesktopMode(), "amp-sim", sf::State::Fullscreen)
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

    volumeSlider = Slider(sf::Vector2f(w * 0.4f, h * 0.5), "Volume", font, &ampSettings.volume);
    gainSlider = Slider(sf::Vector2f(w * 0.6f, h * 0.5), "Gain", font, &ampSettings.gain, 1.0f, 1.5f);
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
        gainSlider.handleEvent(*event, window);
    }
}

void UI::render() {
    window.clear(sf::Color(20, 20, 20));

    volumeSlider.draw(window);
    gainSlider.draw(window);

    window.display();
}