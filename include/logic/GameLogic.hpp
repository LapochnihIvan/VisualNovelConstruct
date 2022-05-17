#ifndef VISUALNOELCOSTRUCT_GAMELOGIC_HPP


#include <string>
#include <vector>
#include <map>
#include <filesystem>
#include <thread>

#include "Reader.hpp"


class GameLogic
{
public:
    static void readPrologue();

    static const std::string& getCurPhraseSoundPath();

    static const std::string& getCurSoundtrackPath();

    static const std::string& getCurBgImgPath();

    static const std::string& getCurPersImgPath();

    static const std::vector<std::string>& getCurTextBlocks();

    static const std::vector<std::string>& getCurAnsTexts();

    static void nextPhrase(std::size_t numAns);

    static bool isEndOfGame();

private:
    struct Phrase
    {
        std::string phraseSoundPath;
        std::string soundtrackPath;
        std::string bgImgPath;
        std::string persImgPath;
        std::vector<std::string> textBlocks;
        std::vector<std::string> ansTexts;
        std::vector<std::string> nextPhrasesPaths;
    };

    struct DefaultSetings
    {
        std::string soundtrackPath;
        std::string bgImgPath;
        std::string persImgPath;
    };
    
    
    static std::map<std::string, Phrase> mScene;
    static DefaultSetings mDefaultSetings;
    static const Phrase* mCurPhrase;
    static bool mIsEndOfGame;

    static void loadSceneSettings(const std::string& sceneName,
                                  const std::string& beginPhraseFileName);
};


#endif //VISUALNOELCOSTRUCT_GAMELOGIC_HPP
