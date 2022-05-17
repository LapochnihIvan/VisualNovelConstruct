#ifndef  VISUALNOELCOSTRUCT_PHRASETEXTAREA
#define VISUALNOELCOSTRUCT_PHRASETEXTAREA


#include <SFML/Window/VideoMode.hpp>

#include "AnimRectWithText.hpp"


class PhraseTextArea : public AnimRectWithText
{
public:
	PhraseTextArea();

	void setBorders(std::vector<std::string>::const_iterator begin,
					std::vector<std::string>::const_iterator end);

	void nextTextBlock();

	bool isEndTextBlocks();

	bool isNotAuthorText();

private:
	std::vector<std::string>::const_iterator mCurBlockPtr;
	std::vector<std::string>::const_iterator mEndBlockPtr;
};


#endif //VISUALNOELCOSTRUCT_PHRASETEXTAREA
