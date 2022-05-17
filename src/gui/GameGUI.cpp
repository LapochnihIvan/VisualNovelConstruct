#include "GameGUI.hpp"
#include <filesystem>

void
GameGUI::process()
{
    mIsGUIruning = true;

    sf::RenderWindow wind(sf::VideoMode::getDesktopMode(),
        "", sf::Style::Fullscreen);
    wind.setFramerateLimit(60U);

    while (wind.isOpen() && !mIsNeedBreakGUI)
    {
        static sf::Event event{};
        while (wind.pollEvent(event))
        {
            if (event.type == sf::Event::EventType::Closed)
            {
                std::exit(0);
            }
            else if (mIsAnsChoiceBlock && mButts.empty())
            {
                mIsAnsChoiceBlock = false;
                mIsPressButt = true;
            }
            else if (mIsAnsChoiceBlock &&
                    sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                for (Button* const& butt : mButts)
                {
                    if (butt->isPressed(wind))
                    {
                        mIsAnsChoiceBlock = false;
                        mNumPressButt = &butt -
#ifdef _WIN32
                        mButts.begin()._Ptr;
#else
                        mButts.begin().base();
#endif //_WIN32
                        mIsPressButt = true;
                    }
                }

            }
            else if (!mIsAnsChoiceBlock &&
                    event.type == sf::Event::EventType::KeyPressed &&
                    event.key.code == sf::Keyboard::Key::Enter)
            {
                if (mPhraseTextArea.isEndTextBlocks())
                {
                    mIsAnsChoiceBlock = true;

                    for (Button*& butt : mButts)
                    {
                        butt->startAnim();
                    }
                }
                else
                {
                    mPhraseTextArea.nextTextBlock();
                    mPhraseTextArea.startAnim();

                    if (mPhraseTextArea.isNotAuthorText())
                    {
                        mPers.changeDir();
                        mPers.startAnim();

                        if (mNasPhraseSound)
                        {
                            mPhraseSound.play();
                        }
                    }
                    else if (mPers.isAppearing())
                    {
                        mPers.changeDir();
                        mPers.startAnim();

                        mPhraseSound.stop();
                    }
                }
            }
        }

        wind.clear(sf::Color::Transparent);

        mMutex.lock();

        wind.draw(mBg);
        if (mIsAnsChoiceBlock)
        {
            for (Button*& butt : mButts)
            {
                wind.draw(*butt);
            }
        }
        else
        {
            wind.draw(mPers);
            wind.draw(mPhraseTextArea);
        }

        mMutex.unlock();

        wind.display();
    }

    wind.close();

    mIsGUIruning = false;
}

std::size_t
GameGUI::getResponse()
{
    while (!mIsPressButt)
    {
        std::this_thread::yield();
    }


    mIsPressButt = false;

    if (!mButts.empty())
    {
        return mNumPressButt;
    }
    
    return 0U;
}

void 
GameGUI::setPhaseSettings(
        const std::string& phraseSoundPath,
        const std::string& soundtrackPath,
        const std::string& bgImgPath,
        const std::string& persImgPath,
        const std::vector<std::string>& textBlocks,
        const std::vector<std::string>& ansTexts)
{
    mPhraseSound.stop();
    if (!phraseSoundPath.empty())
    {
        mNasPhraseSound = true;
        mPhraseSound.openFromFile(phraseSoundPath);
    }
    else
    {
        mNasPhraseSound = false;
    }

    static std::string prevSoundtrackPath;

    if (soundtrackPath != prevSoundtrackPath)
    {
        mSoundtrack.stop();

        if (!soundtrackPath.empty())
        {
            mSoundtrack.openFromFile(soundtrackPath);
            mSoundtrack.setLoop(true);
            mSoundtrack.play();
        }

        prevSoundtrackPath = soundtrackPath;
    }

    mMutex.lock();

    if (!bgImgPath.empty())
    {
        mBg.setImg(bgImgPath);
    }

    if (!persImgPath.empty())
    {
        mPers.setImg(persImgPath);
    }

    mPhraseTextArea.setBorders(textBlocks.begin(), textBlocks.end());
    mPhraseTextArea.startAnim();

    if (mPhraseTextArea.isNotAuthorText())
    {
        mPers.changeDir();
        mPers.startAnim();

        if (mNasPhraseSound)
        {
            mPhraseSound.play();
        }
    }

    for (Button*& butt : mButts)
    {
        delete butt;
    }
    mButts.resize(ansTexts.size());

    float nextButtY(50.F);
    for (std::size_t numButt(0U);
            numButt < ansTexts.size(); ++numButt)
    {
        static sf::Font font;

        if (font.getInfo().family.empty())
        {
            font.loadFromFile("../fontFamily/arial.ttf");
        }

        sf::Text text(sf::String::fromUtf8(ansTexts[numButt].begin(),
                                           ansTexts[numButt].end()),
                      font, 30U * (sf::VideoMode::getDesktopMode().width / 1920.F));

        mButts[numButt] =
                new Button(sf::VideoMode::getDesktopMode().width / 2 - 
                                   text.getLocalBounds().width / 2.F,
                           nextButtY,
                           text.getLocalBounds().width + 10.F,
                           text.getLocalBounds().height + 10.F, ansTexts[numButt]);

        nextButtY += text.getLocalBounds().height + 30.F;
    }

    mMutex.unlock();
}

void
GameGUI::stop()
{
    mIsNeedBreakGUI = true;

    while (mIsGUIruning)
    {
        std::this_thread::yield();
    }
}

sf::Music GameGUI::mPhraseSound;

sf::Music GameGUI::mSoundtrack;

Background GameGUI::mBg;

Person GameGUI::mPers;

PhraseTextArea GameGUI::mPhraseTextArea;

std::vector<Button*> GameGUI::mButts;

std::mutex GameGUI::mMutex;

bool GameGUI::mIsAnsChoiceBlock(false);

bool GameGUI::mIsPressButt(false);

std::size_t GameGUI::mNumPressButt(0U);

bool GameGUI::mIsNeedBreakGUI(false);

bool GameGUI::mIsGUIruning(false);

bool GameGUI::mNasPhraseSound(false);
