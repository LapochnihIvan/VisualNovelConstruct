#include "Button.hpp"


Button::Button(const float x, const float y,
               const float width, const float height,
               const std::string& str) :
        AnimRectWithText(x, y, width, height, 5U)
{
    setStr(str);
}

bool
Button::isPressed(const sf::RenderWindow& window) const
{
    return mRect.getGlobalBounds().contains(
            static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
}
