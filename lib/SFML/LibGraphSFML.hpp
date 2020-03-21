/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** LibGraphSFML
*/

#pragma once

#include "ALibGraph.hpp"
#include <SFML/Graphics.hpp>

extern "C" {
    class LibGraphSFML: public ALibGraph {
        public:
            LibGraphSFML();
            ~LibGraphSFML();
    };
}