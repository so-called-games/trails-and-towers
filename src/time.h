#pragma once
#include <chrono>
#include <functional>
using namespace std;
using namespace chrono;

class Timer
{
public:
    Timer();
    void add(milliseconds delay, function<void()> callback);
};
