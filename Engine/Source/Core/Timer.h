#pragma once

#include "Core/Base.h"
#include "chrono"

namespace Core
{
    class CE_API Timer
    {
    public:
        Timer(const char *name) : name(name), stopped(false)
        {
            startPoint = std::chrono::steady_clock::now();
        }

        ~Timer()
        {
            if (!stopped)
                Stop();
        }

        void Stop()
        {
            auto endPoint = std::chrono::steady_clock::now();

            long long start = std::chrono::time_point_cast<std::chrono::microseconds>(startPoint).time_since_epoch().count();
            long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endPoint).time_since_epoch().count();

            float duration = static_cast<float>(end - start) * 0.001f;

            stopped = true;
        }

    private:
        const char *name;
        std::chrono::time_point<std::chrono::steady_clock> startPoint;
        bool stopped;
    };
}