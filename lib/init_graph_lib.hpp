/*
** EPITECH PROJECT, 2019
** arcade
** File description:
** graph lib init header
*/

#ifndef INIT_HPP_
#define INIT_HPP_

#include <memory>
#include "ILibGraph.hpp"

extern "C" std::unique_ptr<arcade::ILibGraph> init_graph_lib();

#endif
