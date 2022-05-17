#ifndef VISUALNOELCOSTRUCT_READER_HPP


#include <fcntl.h>

#ifndef _WIN32
#    include <unistd.h>

#    include <sys/stat.h>
#endif

#include <string>
#include <vector>
#include <mutex>

#include <rapidxml-1.13/rapidxml.hpp>


class Reader
{
public:
    static void readPhraseSettings(
            const std::string& phrasePath,
            std::string& phraseSoundPath,
            std::string& soundtrackPath,
            std::string& bgImgPath,
            std::string& persImgPath,
            std::vector<std::string>& textBlocks,
            std::vector<std::string>& ansTexts,
            std::vector<std::string>& nextPhrasesPaths);

    static void readDefaultSettings(
            const std::string& sceneName,
            std::string& soundtrackPath,
            std::string& bgImgPath,
            std::string& persImgPath);

private:
    static bool readBuffFromFile(char*& buff,
                                 const char* const& filePath);

    static void readNode(
            std::string& readTarget,
            const std::string&& dir,
            const rapidxml::xml_node<>* const& rootNode,
            const char* nodeName,
            std::size_t nodeNameSize);

    static void readSoundPath(
            std::string& soundPath,
            const rapidxml::xml_node<>* const& rootNode,
            const char* nodeName,
            std::size_t nodeNameSize);
    
    static void readImgPath(
            std::string& imgPath,
            const rapidxml::xml_node<>* const& rootNode,
            const char* nodeName,
            std::size_t nodeNameSize);

    static void readNextPhrase(
            std::string& nextPhrase,
            const rapidxml::xml_node<>* const& ansNode);
};


#endif //VISUALNOELCOSTRUCT_READER_HPP