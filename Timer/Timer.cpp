//
// Created by 檀木筪 on 2024/6/21.
//

#include "Timer.h"


void Timer::start()
{
    if ( !running )
    {
        startTime = std::chrono::high_resolution_clock::now();
        running = true;
    }
}

void Timer::stop()
{
    if ( running )
    {
        auto stopTime = std::chrono::high_resolution_clock::now();
        auto count = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime).count();
        elapsed += count;
        counts.push_back(count);
        running = false;
    }
}

void TimerManager::StartTimer(const String& name)
{
    for (auto& timer: timers)
    {
        if ( timer.getName() == name )
        {
            timer.start();
            return;
        }
    }
    timers.emplace_back(name);
    timers.back().start();
}

void TimerManager::StopTimer(const String& name)
{
    for (auto& timer: timers)
    {
        if ( timer.getName() == name )
        {
            timer.stop();
            return;
        }
    }
}

TimerManager::~TimerManager()
{
    printAll();
}
