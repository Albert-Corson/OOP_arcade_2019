/*
** EPITECH PROJECT, 2019
** arcade
** File description:
** graph lib init header
*/

#ifndef INIT_HPP_
#define INIT_HPP_

#include "ILibGraph.hpp"
#include <memory>

extern "C" std::unique_ptr<arcade::ILibGraph> init_graph_lib();

#endif
