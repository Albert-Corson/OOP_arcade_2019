/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** LibGraphStorage
*/

#include "LibGraphStorage.hpp"

using namespace arcade;

Core::LibGraphStorage::LibGraphStorage(const std::string &libPath, const std::string &libName, const libGraphLoader_t &libLoader)
    : LibInfo(libPath, libName)
    , loader(libLoader)
    , instance(nullptr)
{
}

Core::LibGraphStorage::LibGraphStorage(const Core::LibGraphStorage &other)
    : LibInfo(other)
    , loader(other.loader)
    , instance(nullptr)
{
}

Core::LibGraphStorage &Core::LibGraphStorage::operator=(const Core::LibGraphStorage &other)
{
    LibInfo::operator=(other);
    this->loader = other.loader;
    this->instance = nullptr;
    return (*this);
}
