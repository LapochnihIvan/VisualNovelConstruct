#include "PhraseTextArea.hpp"


PhraseTextArea::PhraseTextArea() :
		AnimRectWithText(0.F,
						 sf::VideoMode::getDesktopMode().height -
						 		sf::VideoMode::getDesktopMode().height / 6U,
						 sf::VideoMode::getDesktopMode().width,
						 sf::VideoMode::getDesktopMode().height / 6U,
						 10U)
{
	mRect.setOutlineThickness(1.F);
	mRect.setOutlineColor(sf::Color::Black);
}

void
PhraseTextArea::setBorders(std::vector<std::string>::const_iterator begin,
						   std::vector<std::string>::const_iterator end)
{
	mCurBlockPtr = begin;
	mEndBlockPtr = end - 1;

	setStr(*mCurBlockPtr);
}

void
PhraseTextArea::nextTextBlock()
{
	setStr(*++mCurBlockPtr);
}

bool
PhraseTextArea::isEndTextBlocks()
{
	return mCurBlockPtr == mEndBlockPtr;
}

bool
PhraseTextArea::isNotAuthorText()
{
	return mCurBlockPtr->front() == '-';
}
