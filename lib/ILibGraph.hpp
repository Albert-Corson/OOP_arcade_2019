/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** ILibGraph
*/

#pragma once

#include <cstddef>

extern "C" {
    class ILibGraph {
        public:
            ILibGraph() = default;
            virtual ~ILibGraph() = default;

            virtual void createWindow(std::size_t width, std::size_t height) = 0;
            virtual void render() const = 0;
    };
}