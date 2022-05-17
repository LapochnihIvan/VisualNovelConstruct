#include "Person.hpp"


Person::Person() :
	    BaseAnimObject([this]()
        {
            while (!mNeedBreakAnimThread && mDir == 1 ? isNotVisible() : isVisible())
            {
                mSprite.setColor(sf::Color(255U, 255U, 255U, 
                                           mSprite.getColor().a + 5U * mDir));

                std::this_thread::sleep_for(
                    std::chrono::milliseconds(10U));
            }

            mIsRunning = false;
        }),
        mX(0.F),
        mScaleFactor(0.F),
        mDir(0)
{

}

void
Person::setImg(const std::string& imgPath)
{
    stopAnim();

    static sf::Texture persTexture;
    persTexture.loadFromFile(imgPath);

    mSprite.setTexture(persTexture, true);
    mScaleFactor = (mDesktopHeight - 200.F) / mSprite.getLocalBounds().height;
    mSprite.setScale(mScaleFactor, mScaleFactor);

    mX = mDesktopWidth - mSprite.getLocalBounds().width * mScaleFactor - 10.F;
    mSprite.setPosition(mX, mDesktopHeight - mSprite.getLocalBounds().height * mScaleFactor);

    mSprite.setColor(sf::Color(255U, 255U, 255U, 0U));

    mDir = -1;
}

void
Person::changeDir()
{
    mDir = mDir == 1 ? -1 : 1;
}

bool
Person::isAppearing()
{
    return mDir == 1;
}

std::uint32_t Person::mDesktopWidth(sf::VideoMode::getDesktopMode().width);
std::uint32_t Person::mDesktopHeight(sf::VideoMode::getDesktopMode().height);

bool
Person::isVisible()
{
    return mSprite.getColor().a > 0U;
}

bool
Person::isNotVisible()
{
    return mSprite.getColor().a < 255U;
}

void
Person::draw(sf::RenderTarget& target,
             sf::RenderStates states) const
{
    target.draw(mSprite, states);
}
