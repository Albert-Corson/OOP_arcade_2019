/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** ALibGraph
*/

#pragma once

#include "ILibGraph.hpp"

namespace arcade {
    class ALibGraph : public ILibGraph {
        public:
            virtual ~ALibGraph() = default;

        protected:
            ALibGraph() = default;
    };
}
