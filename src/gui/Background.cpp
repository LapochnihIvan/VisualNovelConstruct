#include "Background.hpp"


void
Background::setImg(const std::string& imgPath)
{
	static sf::Texture bgTexture;

	bgTexture.loadFromFile(imgPath);

	mSprite.setTexture(bgTexture, true);
	mSprite.setScale(mDesktopWidth / mSprite.getLocalBounds().width,
				     mDesktopHeight / mSprite.getLocalBounds().height);
}

std::uint32_t Background::mDesktopWidth(sf::VideoMode::getDesktopMode().width);
std::uint32_t Background::mDesktopHeight(sf::VideoMode::getDesktopMode().height);

void
Background::draw(sf::RenderTarget& target,
			     sf::RenderStates states) const
{
	target.draw(mSprite, states);
}
