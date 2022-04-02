#pragma once
#include <thread>
#include <chrono>
#include <functional>
using namespace std;

class Timer
{
public:
    Timer();
    void add(chrono::milliseconds delay, function<void()> callback);
};
