#include "GameLogic.hpp"
#include "GameGUI.hpp"

#ifndef _WIN32
#    include <X11/Xlib.h>
#endif //_WIN32

using std::operator""s;


int main()
{
#ifndef _WIN32
    ::XInitThreads();
#endif //_WIN32

    std::filesystem::current_path("../scenes"s);

    GameLogic::readPrologue();

    std::thread(GameGUI::process).detach();

    while (!GameLogic::isEndOfGame())
    {
        GameGUI::setPhaseSettings(GameLogic::getCurPhraseSoundPath(),
                                  GameLogic::getCurSoundtrackPath(),
                                  GameLogic::getCurBgImgPath(),
                                  GameLogic::getCurPersImgPath(),
                                  GameLogic::getCurTextBlocks(),
                                  GameLogic::getCurAnsTexts());

        GameLogic::nextPhrase(GameGUI::getResponse());
    }

    GameGUI::stop();

    return 0;
}
