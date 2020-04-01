/*
** EPITECH PROJECT, 2019
** arcade
** File description:
** graph lib init header
*/

#pragma once

#include <memory>
#include "ILibGraph.hpp"

extern "C" std::unique_ptr<arcade::ILibGraph> init_graph_lib();
