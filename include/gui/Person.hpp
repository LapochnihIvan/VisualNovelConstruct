#ifndef VISUALNOELCOSTRUCT_PERSON_HPP
#define VISUALNOELCOSTRUCT_PERSON_HPP


#include <SFML/Window/VideoMode.hpp>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "BaseAnimObject.hpp"


class Person : public BaseAnimObject
{
public:
    Person();

    void setImg(const std::string& imgPath);

    void changeDir();

    bool isAppearing();

private:
    sf::Sprite mSprite;
    float mX;
    float mScaleFactor;
    std::int8_t mDir;

    static std::uint32_t mDesktopWidth;
    static std::uint32_t mDesktopHeight;

    bool isVisible();
    bool isNotVisible();

    void draw(sf::RenderTarget& target,
              sf::RenderStates states) const final;
};


#endif //VISUALNOELCOSTRUCT_PERSON_HPP