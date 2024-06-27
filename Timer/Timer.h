//
// Created by 檀木筪 on 2024/6/21.
//

#ifndef QT_PRJ_IMAGE_EDITOR_TIMER_H
#define QT_PRJ_IMAGE_EDITOR_TIMER_H

#include "Define.h"

class Timer
{
public:
    Timer(const String& name) : name(name), running(false), elapsed(0)
    {
        counts = Vector<long long>();
    }

    void start();
    void stop();
    [[nodiscard]] inline long long getElapsedMicroseconds() const{
        return elapsed;
    }
    [[nodiscard]] inline const String& getName() const{
        return name;
    }
    [[nodiscard]] inline const Vector<long long>& getCounts() const{
        return counts;
    }

private:
    const String name;
    bool running;
    long long elapsed;
    Vector<long long> counts;
    std::chrono::high_resolution_clock::time_point startTime;
};

class TimerManager
{
public:
    static TimerManager& Instance()
    {
        static TimerManager instance;
        return instance;
    }
    void StartTimer(const String& name);
    void StopTimer(const String& name);
    ~TimerManager();
private:
    inline void printAll() const
    {
        for (const auto& timer: timers)
        {
            auto avg = !timer.getCounts().empty() ? timer.getElapsedMicroseconds() / timer.getCounts().size() : 0;
            std::cout << std::fixed
                      << std::format("Timer::{} 合计花费 {} ms, 共唤起 {} 次, 平均花费 {} ms\n",
                                     timer.getName(), timer.getElapsedMicroseconds(),
                                     timer.getCounts().size(), avg);
        }
    }
    TimerManager() = default;
    Vector<Timer> timers;
};

#endif //QT_PRJ_IMAGE_EDITOR_TIMER_H
