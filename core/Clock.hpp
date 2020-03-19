/*
** EPITECH PROJECT, 2020
** Pacman
** File description:
** Clock
*/

#pragma once

#include <chrono>

typedef std::chrono::_V2::steady_clock::time_point time_point_t;

class Clock {
    public:
        Clock();
        ~Clock() = default;
        void restart() noexcept;
        long long getElapsedNanoseconds() const noexcept;
        long long getElapsedMicroseconds() const noexcept;
        long long getElapsedMilliseconds() const noexcept;
        long long getElapsedSeconds() const noexcept;

    private:
        time_point_t _start;
};
