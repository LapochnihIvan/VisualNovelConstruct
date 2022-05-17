#ifndef VISUALNOVELCONSTRUCT_BACKGROUND_HPP
#define VISUALNOVELCONSTRUCT_BACKGROUND_HPP


#include <SFML/Window/VideoMode.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


class Background : public sf::Drawable
{
public:
    void setImg(const std::string& imgPath);

private:
    sf::Sprite mSprite;

    static std::uint32_t mDesktopWidth;
    static std::uint32_t mDesktopHeight;

    void draw(sf::RenderTarget& target,
              sf::RenderStates states) const final;
};


#endif //VISUALNOVELCONSTRUCT_BACKGROUND_HPP
