/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** LibGraphNcurses
*/

#pragma once

#include "ALibGraph.hpp"

extern "C" {
    class LibGraphNcurses: public ALibGraph {
        public:
            LibGraphNcurses();
            ~LibGraphNcurses();

            virtual void createWindow(std::size_t width, std::size_t height);
            virtual void render() const;

        protected:
    };
}