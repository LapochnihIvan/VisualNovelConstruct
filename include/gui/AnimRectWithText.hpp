#ifndef VISUALNOVELCONSTRUCT_OBJECTWITHANIMTEXT_HPP
#define VISUALNOVELCONSTRUCT_OBJECTWITHANIMTEXT_HPP


#include <string>
#include <functional>
#include <thread>

#include <SFML/Window/VideoMode.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "BaseAnimObject.hpp"


class AnimRectWithText : public BaseAnimObject
{
protected:
    sf::RectangleShape mRect;

    explicit AnimRectWithText(float x,
                              float y,
                              float width,
                              float height,
                              const std::size_t&& animSleepMillisecs);

    void setStr(const std::string& str);

private:
    sf::Text mText;
    std::basic_string<sf::Uint32> mUtf32Str;

    void draw(sf::RenderTarget& target,
              sf::RenderStates states) const final;
};

#endif //VISUALNOVELCONSTRUCT_OBJECTWITHANIMTEXT_HPP
