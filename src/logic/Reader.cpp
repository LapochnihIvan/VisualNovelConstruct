#include "Reader.hpp"

#ifdef _WIN32
#include <windows.h>
#endif //_WIN32

using std::operator""s;


#define ITERATE_NODES(iteratorName, nodeName, nodeNameSize)                    \
for (const rapidxml::xml_node<>* iteratorName(                                 \
            rootNode->first_node(nodeName, nodeNameSize));                     \
            iteratorName != nullptr;                                           \
            iteratorName = iteratorName->next_sibling(nodeName, nodeNameSize))

void
Reader::readPhraseSettings(const std::string& phrasePath,
                           std::string& phraseSoundPath,
                           std::string& soundtrackPath,
                           std::string& bgImgPath,
                           std::string& persImgPath,
                           std::vector<std::string>& textBlocks,
                           std::vector<std::string>& ansTexts,
                           std::vector<std::string>& nextPhrasesPaths)
{
    rapidxml::xml_document<> document;

    char* xmlBuff;
    if (!readBuffFromFile(xmlBuff, phrasePath.c_str()))
    {
        return;
    }

    try
    {
        document.parse<rapidxml::parse_default>(xmlBuff);
    }
    catch (rapidxml::parse_error)
    {
        std::fwrite(("Error in"s + phrasePath).c_str(),
                    1, 8 + phrasePath.length(), stderr);
    }

    const rapidxml::xml_node<>* const rootNode(document.first_node());

    readSoundPath(phraseSoundPath, rootNode, "PhraseSoundPath", 15U);
    readSoundPath(soundtrackPath, rootNode, "SoundtrackPath", 14U);
    readImgPath(bgImgPath, rootNode, "BgImgPath", 9U);
    readImgPath(persImgPath, rootNode, "PersImgPath", 11U);

    ITERATE_NODES(textBlockNode, "TextBlock", 9U)
    {
        textBlocks.emplace_back(std::string(textBlockNode->value(),
                                            textBlockNode->value_size()));
    }

    ITERATE_NODES(ansNode, "Ans", 3U)
    {
        ansTexts.emplace_back(std::string(ansNode->value(),
                                          ansNode->value_size()));

        readNextPhrase(nextPhrasesPaths.emplace_back(), ansNode);
    }

    if (ansTexts.empty())
    {
        readNode(nextPhrasesPaths.emplace_back(), ""s,
                 rootNode, "NextPhrasePath", 14U);
    }

    document.remove_all_nodes();
    document.remove_all_attributes();

    delete[] xmlBuff;
}

void
Reader::readDefaultSettings(const std::string& sceneName,
                            std::string& soundtrackPath,
                            std::string& bgImgPath,
                            std::string& persImgPath)
{
    rapidxml::xml_document<> document;

    char* xmlBuff;
    if (!readBuffFromFile(xmlBuff, (sceneName + "default.xml"s).c_str()))
    {
        return;
    }
    document.parse<rapidxml::parse_default>(xmlBuff);

    const rapidxml::xml_node<>* const rootNode(document.first_node());

    readSoundPath(soundtrackPath, rootNode, "SoundtrackPath", 14U);
    readImgPath(bgImgPath, rootNode, "BgImgPath", 9U);
    readImgPath(persImgPath, rootNode, "PersImgPath", 11U);

    document.remove_all_nodes();
    document.remove_all_attributes();

    delete[] xmlBuff;
}

bool
Reader::readBuffFromFile(char*& buff, const char* const& filePath)
{
#ifdef _WIN32
    ::HANDLE hFile(::CreateFileA(filePath, GENERIC_READ, 0x00, nullptr,
                                 OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr));

    if (hFile == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    ::DWORD fSize(::GetFileSize(hFile, nullptr));

    buff = new char[fSize + 1];
    buff[fSize] = '\000';

    ::ReadFile(hFile, static_cast<void*>(buff), fSize, nullptr, nullptr);

    ::CloseHandle(hFile);
#else
    const int fd(::open(filePath, O_RDONLY));

    if (fd == -1)
    {
        return false;
    }

    struct ::stat fileInfo;
    ::fstat(fd, &fileInfo);

    buff = new char[fileInfo.st_size + 1];
    buff[fileInfo.st_size] = '\000';

    ::read(fd, static_cast<void*>(buff), fileInfo.st_size);

    ::close(fd);
#endif

    return true;
}

void
Reader::readNode(
        std::string& readTarget,
        const std::string&& dir,
        const rapidxml::xml_node<>* const& rootNode,
        const char* nodeName,
        const std::size_t nodeNameSize)
{
    const rapidxml::xml_node<>* const requiredNode(
            rootNode->first_node(nodeName, nodeNameSize));

    if (requiredNode != nullptr)
    {
        readTarget = dir + 
                std::string(requiredNode->value(),
                            requiredNode->value_size());
    }
}

void
Reader::readSoundPath(
        std::string& soundPath,
        const rapidxml::xml_node<>* const& rootNode,
        const char* nodeName,
        const std::size_t nodeNameSize)
{
    readNode(soundPath, "../audio/"s, rootNode,
             nodeName, nodeNameSize);
}

void
Reader::readImgPath(
        std::string& imgPath,
        const rapidxml::xml_node<>* const& rootNode,
        const char* nodeName,
        const std::size_t nodeNameSize)
{
    readNode(imgPath, "../imgs/"s, rootNode,
             nodeName, nodeNameSize);
}

void
Reader::readNextPhrase(std::string& nextPhrase,
                       const rapidxml::xml_node<>* const& ansNode)
{
    const rapidxml::xml_attribute<>* nextPhaseAttr(
            ansNode->first_attribute("nextPhrasePath", 14U));
    
    nextPhrase = std::string(nextPhaseAttr->value(),
                             nextPhaseAttr->value_size());
}
