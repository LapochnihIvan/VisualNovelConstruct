#ifndef VISUALNOVELCONSTRUCT_GAMEGUI_HPP
#define VISUALNOVELCONSTRUCT_GAMEGUI_HPP


#include <SFML/Graphics/RenderWindow.hpp>

#include <SFML/Audio/Music.hpp>

#include "Background.hpp"
#include "Person.hpp"
#include "PhraseTextArea.hpp"
#include "Button.hpp"


class GameGUI
{
public:
    static void process();

    static std::size_t getResponse();

    static void setPhaseSettings(
            const std::string& phraseSoundPath,
            const std::string& soundtrackPath,
            const std::string& bgImgPath,
            const std::string& persImgPath,
            const std::vector<std::string>& textBlocks,
            const std::vector<std::string>& ansTexts);

    static void stop();

private:
    static sf::Music mPhraseSound;
    static sf::Music mSoundtrack;
    static Background mBg;
    static Person mPers;
    static PhraseTextArea mPhraseTextArea;
    static std::vector<Button*> mButts;
    static std::mutex mMutex;
    static bool mIsAnsChoiceBlock;
    static bool mIsPressButt;
    static std::size_t mNumPressButt;
    static bool mIsNeedBreakGUI;
    static bool mIsGUIruning;
    static bool mNasPhraseSound;
};


#endif //VISUALNOVELCONSTRUCT_GAMEGUI_HPP
