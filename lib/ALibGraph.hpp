/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** ALibGraph
*/

#pragma once

#include "ILibGraph.hpp"
#include "deps/Exception.hpp"
#include "init_graph_lib.hpp"
#include "get_lib_name.hpp"

namespace arcade {
    class ALibGraph : public ILibGraph {
        public:
            class Exception;

            virtual ~ALibGraph() = default;

        protected:
            ALibGraph() = default;
    };

    class ALibGraph::Exception : public arcade::Exception {
        public:
            Exception(const std::string &message)
                : arcade::Exception(message)
            {
            };

            const char *what() const throw() override
            {
                return (("ALibGraph::Exception " + _msg).c_str());
            };
    };
}
