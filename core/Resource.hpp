/*
** EPITECH PROJECT, 2020
** OOP_arcade_2020
** File description:
** resource class
*/

#pragma once

#include <string>

namespace arcade {
    class Resource {
        public:
            Resource(const std::string &filepathGraph, const std::string &filepathAscii);

            std::string const &getFilepathGraph() const;
            std::string const &getFilepathAscii() const;

        private:
            std::string _filepathGraph;
            std::string _filepathAscii;
    };

}
