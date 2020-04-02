/*
** EPITECH PROJECT, 2020
** OOP_arcade_2020
** File description:
** resource_path.cpp
*/

#include "Resource.hpp"
#include <utility>

using namespace arcade;

Resource::Resource(const std::string &filepathGraph, const std::string &filepathAscii)
    : _filepathGraph(std::move(filepathGraph))
    , _filepathAscii(std::move(filepathAscii))
{
}

std::string const &Resource::getFilepathGraph() const
{
    return _filepathGraph;
}

std::string const &Resource::getFilepathAscii() const
{
    return _filepathAscii;
}
