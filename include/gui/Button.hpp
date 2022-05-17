#ifndef VISUALNOVELCONSTRUCT_BUTTON_HPP
#define VISUALNOVELCONSTRUCT_BUTTON_HPP


#include <SFML/Graphics.hpp>

#include "AnimRectWithText.hpp"


class Button : public AnimRectWithText
{
public:
    Button(float x, float y,
           float width, float height,
           const std::string& str);
    
    bool isPressed(const sf::RenderWindow& window) const;

private:
    using AnimRectWithText::setStr;
};


#endif //VISUALNOVELCONSTRUCT_BUTTON_HPP
