/*
** EPITECH PROJECT, 2020
** Pacman
** File description:
** Clock
*/

#include "Clock.hpp"

using namespace arcade;

Clock::Clock()
    : _start(std::chrono::steady_clock::now())
{
}

void Clock::reset()
{
    _start = std::chrono::steady_clock::now();
}

long Clock::getElapsedTime()
{
    const auto &end = std::chrono::steady_clock::now();

    return (std::chrono::duration_cast<std::chrono::milliseconds>(end - _start).count());
}
