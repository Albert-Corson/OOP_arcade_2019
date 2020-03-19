/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** ALibGraph
*/

#pragma once

#include <cstddef>

extern "C" {
    class ALibGraph {
        public:
            ALibGraph() = default;
            virtual ~ALibGraph() = default;

            virtual void createWindow(std::size_t width, std::size_t height) = 0;
            virtual void render() const = 0;

        protected:
            std::size_t _winWidth;
            std::size_t _winHeight;
    };
}