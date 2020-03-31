/*
** EPITECH PROJECT, 2020
** Pacman
** File description:
** Clock
*/

#pragma once

#include "IClock.hpp"
#include <chrono>


namespace arcade {
    class Clock : public IClock {
        public:
            Clock();
            ~Clock() = default;
            void reset() override;
            long getElapsedTime() override;

        private:
            std::chrono::_V2::steady_clock::time_point _start;
    };
}