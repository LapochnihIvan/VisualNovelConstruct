#include "AnimRectWithText.hpp"

using std::operator""s;


AnimRectWithText::AnimRectWithText(const float x,
                                   const float y,
                                   const float width,
                                   const float height,
                                   const std::size_t&& animSleepMillisecs) :
        BaseAnimObject([this, animSleepMillisecs]()
        {
            std::basic_string<sf::Uint32>::iterator curEndPtr(mUtf32Str.begin());

            while (!mNeedBreakAnimThread &&
                   curEndPtr != mUtf32Str.end())
            {
                curEndPtr++;

                mText.setString(sf::String(
                        std::basic_string<sf::Uint32>(mUtf32Str.begin(), curEndPtr)));

                std::this_thread::sleep_for(
                        std::chrono::milliseconds(animSleepMillisecs));
            }

            mIsRunning = false;
        }),
        mRect(sf::Vector2f(width, height))
{
    mRect.setPosition(x, y);
    mRect.setFillColor(sf::Color(169U, 169U, 169U, 150U));

    static sf::Font font;

    if (font.getInfo().family.empty())
    {
        font.loadFromFile("../fontFamily/arial.ttf"s);
    }

    mText.setFont(font);
    mText.setCharacterSize(30U * (sf::VideoMode::getDesktopMode().width / 1920.F));
    mText.setFillColor(sf::Color::Black);

    mText.setPosition(x, y);
}

void
AnimRectWithText::setStr(const std::string& str)
{
    stopAnim();

    mUtf32Str.clear();

    sf::Utf8::toUtf32(str.begin(), str.end(),
                      std::back_inserter(mUtf32Str));
}

void
AnimRectWithText::draw(sf::RenderTarget& target,
                       sf::RenderStates states) const
{
    target.draw(mRect);
    target.draw(mText);
}
