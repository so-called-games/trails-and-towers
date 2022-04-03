#include "time.h"

Timer::Timer() {}

void Timer::add(milliseconds delay, function<void()> callback)
{
    thread([=]()
        {
            this_thread::sleep_for(chrono::milliseconds(delay));
            callback();
        }).detach();
}
