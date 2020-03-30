/*
** EPITECH PROJECT, 2020
** OOP_arcade_2020
** File description:
** resource_path.cpp
*/

#include "Resource.hpp"
#include <utility>

using namespace arcade;

Resource::Resource(ResourceType rsrcType, const std::string &filepathGraph, const std::string &filepathAscii)
    : _type { rsrcType }
    , _filepathGraph { std::move(filepathGraph) }
    , _filepathAscii { std::move(filepathAscii) }
{
}

bool Resource::isType(ResourceType type) const
{
    return _type & type;
}

bool Resource::isTypeAudio() const
{
    return _type & ResourceType::AUDIO;
}

bool Resource::isTypeImg() const
{
    return _type & ResourceType::IMG;
}

std::string const &Resource::getFilepathGraph() const
{
    return _filepathGraph;
}

std::string const &Resource::getFilepathAscii() const
{
    return _filepathAscii;
}
