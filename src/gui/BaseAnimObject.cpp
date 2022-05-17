#include "BaseAnimObject.hpp"


BaseAnimObject::BaseAnimObject(const std::function<void()>& act) :
		mAct(act),
        mIsRunning(false),
        mNeedBreakAnimThread(false)
{

}

void
BaseAnimObject::startAnim()
{
    if (!mIsRunning)
    {
        mIsRunning = true;

        std::thread(mAct).detach();
    }
}

void
BaseAnimObject::stopAnim()
{
    mNeedBreakAnimThread = true;

    while (mIsRunning)
    {
        std::this_thread::yield();
    }

    mNeedBreakAnimThread = false;
}
