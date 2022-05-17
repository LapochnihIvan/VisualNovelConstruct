#ifndef VISUALNOVELCONSTRUCT_BASEANIMOBJECT_HPP
#define VISUALNOVELCONSTRUCT_BASEANIMOBJECT_HPP


#include <functional>
#include <thread>
#include <mutex>

#include <SFML/Graphics/Drawable.hpp>


class BaseAnimObject : public sf::Drawable
{
public:
	explicit BaseAnimObject(const std::function<void()>& act);

	void startAnim();

	void stopAnim();

protected:
	bool mIsRunning;
	bool mNeedBreakAnimThread;

private:
	std::function<void()> mAct;
};


#endif //VISUALNOVELCONSTRUCT_BASEANIMOBJECT_HPP
