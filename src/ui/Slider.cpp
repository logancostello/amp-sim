#include "Slider.h"
#include <cmath>

Slider::Slider(
    sf::Vector2f pos, 
    const std::string& label, 
    sf::Font font,
    float value,
    float min, 
    float max
): pos(pos), label(label), font(font), value(value), min(min), max(max) {}

float Slider::valueToHandleY() const {
    float trackTop = pos.y - trackHeight / 2.0f;
    float normalized = 1.0f - (value - min) / (max - min);
    return trackTop + normalized * trackHeight;
}

float Slider::handleYToValue(float y) const {
    float trackTop = pos.y - trackHeight / 2.0f;
    float normalized = (y - trackTop) / trackHeight;
    normalized = std::clamp(normalized, 0.0f, 1.0f);
    return min + (1.0f - normalized) * (max - min);
}

sf::FloatRect Slider::handleBounds() const {
    float handleY = valueToHandleY();
    return sf::FloatRect(
        sf::Vector2f(pos.x - handleW / 2, handleY - handleH / 2),
        sf::Vector2f(handleW, handleH)
    );
}

void Slider::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (event.is<sf::Event::MouseButtonPressed>())
        if (handleBounds().contains(mouse))
            dragging = true;

    if (event.is<sf::Event::MouseButtonReleased>())
        dragging = false;

    if (event.is<sf::Event::MouseMoved>() && dragging)
        value = handleYToValue(mouse.y);
}

void Slider::draw(sf::RenderWindow& window) {

    // draw label
    sf::Text text(font, label, fontSize);
    text.setFillColor(fontColor);
    text.setPosition(sf::Vector2f(pos.x - text.getLocalBounds().size.x / 2.0f, pos.y - trackHeight / 2.0f - 40.0f));
    window.draw(text);

    // draw track
    sf::RectangleShape track(sf::Vector2f(trackWidth, trackHeight));
    track.setFillColor(trackColor);
    track.setPosition(sf::Vector2f(pos.x - trackWidth / 2.0f, pos.y - trackHeight / 2.0f));
    window.draw(track);

    // draw handle
    float handleY = valueToHandleY();
    sf::RectangleShape handle(sf::Vector2f(handleW, handleH));
    handle.setFillColor(handleColor);
    handle.setPosition(sf::Vector2f(pos.x - handleW / 2.0f, handleY - handleH / 2.0f));
    window.draw(handle);
}