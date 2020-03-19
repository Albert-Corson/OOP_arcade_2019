/*
** EPITECH PROJECT, 2020
** Pacman
** File description:
** Clock
*/

#include "Clock.hpp"

template<typename T>
static long long getElapsed(const time_point_t &start) noexcept
{
    auto end = std::chrono::steady_clock::now();

    return (std::chrono::duration_cast<T>(end - start).count());
}

Clock::Clock()
    : _start(std::chrono::steady_clock::now())
{
}

void Clock::restart() noexcept
{
    _start = std::chrono::steady_clock::now();
}

long long Clock::getElapsedNanoseconds() const noexcept
{
    return (getElapsed<std::chrono::nanoseconds>(_start));
}

long long Clock::getElapsedMicroseconds() const noexcept
{
    return (getElapsed<std::chrono::microseconds>(_start));
}

long long Clock::getElapsedMilliseconds() const noexcept
{
    return (getElapsed<std::chrono::milliseconds>(_start));
}

long long Clock::getElapsedSeconds() const noexcept
{
    return (getElapsed<std::chrono::seconds>(_start));
}
