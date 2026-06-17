#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Slider {
public:
    Slider(
        sf::Vector2f pos,
        const std::string& label, 
        sf::Font font,
        float* value,
        float min = 0.0f, 
        float max = 1.0f
    );

    Slider() = default;

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

private:
    sf::Vector2f pos; // center
    std::string label;
    sf::Font font;
    float* value;
    float min, max;

    bool dragging = false;

    static constexpr float trackWidth = 10.0f;
    static constexpr float trackHeight = 500.0f;
    static constexpr float handleW = 50.0f;
    static constexpr float handleH = 18.0f;
    static constexpr sf::Color trackColor = sf::Color(80, 80, 80);
    static constexpr sf::Color handleColor = sf::Color(200, 200, 200);
    static constexpr sf::Color fontColor = sf::Color(180, 180, 180);
    static constexpr int fontSize = 24;

    float valueToHandleY() const;
    float handleYToValue(float y) const;
    sf::FloatRect handleBounds() const;
};