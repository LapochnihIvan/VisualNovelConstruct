#include "GameLogic.hpp"

using std::operator""s;


void
GameLogic::readPrologue()
{
    loadSceneSettings("prologue/"s, "beginPhrase.xml"s);
}

const std::string&
GameLogic::getCurPhraseSoundPath()
{
    return mCurPhrase->phraseSoundPath;
}

const std::string&
GameLogic::getCurSoundtrackPath()
{
    return mCurPhrase->soundtrackPath.empty() ?
            mDefaultSetings.soundtrackPath :
            mCurPhrase->soundtrackPath;
}

const std::string&
GameLogic::getCurBgImgPath()
{
    return mCurPhrase->bgImgPath.empty() ?
            mDefaultSetings.bgImgPath :
            mCurPhrase->bgImgPath;
}

const std::string&
GameLogic::getCurPersImgPath()
{
    return mCurPhrase->persImgPath.empty() ?
            mDefaultSetings.persImgPath :
            mCurPhrase->persImgPath;
}

const std::vector<std::string>&
GameLogic::getCurTextBlocks()
{
    return mCurPhrase->textBlocks;
}

const std::vector<std::string>&
GameLogic::getCurAnsTexts()
{
    return mCurPhrase->ansTexts;
}

void
GameLogic::nextPhrase(std::size_t numAns)
{
    if (mCurPhrase->nextPhrasesPaths[numAns].empty())
    {
        mIsEndOfGame = true;

        return;
    }

    const std::string& nextPhrasePath(
            mCurPhrase->nextPhrasesPaths[numAns]);
    
    std::size_t slashPos(nextPhrasePath.find('/'));
    
    if (slashPos != std::string::npos)
    {
        ++slashPos;
        const std::string& beginPhraseFileName(
                nextPhrasePath.substr(slashPos));

        loadSceneSettings(nextPhrasePath.substr(UINT64_C(0), slashPos),
                          beginPhraseFileName);
    }
    else
    {
        mCurPhrase = &mScene[nextPhrasePath];
    }
}

bool
GameLogic::isEndOfGame()
{
    return mIsEndOfGame;
}

std::map<std::string, GameLogic::Phrase> GameLogic::mScene;

GameLogic::DefaultSetings GameLogic::mDefaultSetings;

const GameLogic::Phrase* GameLogic::mCurPhrase(nullptr);

bool GameLogic::mIsEndOfGame(false);

void
GameLogic::loadSceneSettings(const std::string& sceneName,
                             const std::string& beginPhraseFileName)
{
    mScene.clear();

    Phrase* curReadingPhase;
    for (const std::filesystem::directory_entry& phraseFile :
            std::filesystem::directory_iterator(sceneName))
    {
        std::string fileName(phraseFile.path().filename().string());
        if (fileName != beginPhraseFileName &&
                fileName != "default.xml"s)
        {
            curReadingPhase = &mScene[fileName];
            std::thread(Reader::readPhraseSettings,
                        phraseFile.path().string(),
                        std::ref(curReadingPhase->phraseSoundPath),
                        std::ref(curReadingPhase->soundtrackPath),
                        std::ref(curReadingPhase->bgImgPath),
                        std::ref(curReadingPhase->persImgPath),
                        std::ref(curReadingPhase->textBlocks),
                        std::ref(curReadingPhase->ansTexts),
                        std::ref(curReadingPhase->nextPhrasesPaths)).detach();
        }
    }

    Reader::readDefaultSettings(sceneName, mDefaultSetings.soundtrackPath,
                                mDefaultSetings.bgImgPath,
                                mDefaultSetings.persImgPath);

    curReadingPhase = &mScene[beginPhraseFileName];
    Reader::readPhraseSettings(
            sceneName + beginPhraseFileName,
            curReadingPhase->phraseSoundPath,
            curReadingPhase->soundtrackPath,
            curReadingPhase->bgImgPath,
            curReadingPhase->persImgPath,
            curReadingPhase->textBlocks,
            curReadingPhase->ansTexts,
            curReadingPhase->nextPhrasesPaths);

    mCurPhrase = curReadingPhase;
}
