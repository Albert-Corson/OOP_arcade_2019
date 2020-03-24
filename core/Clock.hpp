/*
** EPITECH PROJECT, 2020
** Pacman
** File description:
** Clock
*/

#pragma once

#include "IClock.hpp"
#include <chrono>

typedef std::chrono::_V2::steady_clock::time_point time_point_t;

namespace arcade {
    class Clock : public IClock {
        public:
            Clock();
            ~Clock() = default;
            void reset() noexcept override;
            long getElapsedNanoseconds() const noexcept override;
            long getElapsedMicroseconds() const noexcept override;
            long getElapsedMilliseconds() const noexcept override;
            long getElapsedSeconds() const noexcept override;

        private:
            time_point_t _start;
    };
}