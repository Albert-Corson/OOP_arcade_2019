/*
** EPITECH PROJECT, 2020
** OOP_arcade_2020
** File description:
** resource_path.cpp
*/

#include "Resource.hpp"
#include <utility>

using namespace arcade;

Resource::Resource(ResourceType rsrcType, std::string &filepathGraph, std::string &filepathAscii)
    : type { rsrcType }
    , filepath_graph { std::move(filepathGraph) }
    , filepath_ascii { std::move(filepathAscii) }
{
}

bool Resource::isType(ResourceType ofType) const
{
    return this->type & type;
}

bool Resource::isTypeAudio() const
{
    return this->type & ResourceType::AUDIO;
}

bool Resource::isTypeImg() const
{
    return this->type & ResourceType::IMG;
}

std::string const &Resource::getFilepathGraph() const
{
    return this->filepath_graph;
}

std::string const &Resource::getFilepathAscii() const
{
    return this->filepath_ascii;
}
