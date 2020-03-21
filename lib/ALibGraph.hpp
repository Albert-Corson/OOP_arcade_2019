/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** ALibGraph
*/

#pragma once

#include <cstddef>

#include "ILibGraph.hpp"

extern "C" {
    class ALibGraph : public ILibGraph {
        public:
            virtual ~ALibGraph() = default;
    };
}