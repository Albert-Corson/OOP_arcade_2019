/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** LibGraphStorage
*/

#pragma once

#include "Core.hpp"

namespace arcade {
    struct Core::LibGraphStorage : public ICore::LibInfo {
        LibGraphStorage(const std::string &libPath = "", const std::string &libName = "", const libGraphLoader_t &libLoader = nullptr);
        LibGraphStorage(const LibGraphStorage &other);
        LibGraphStorage &operator=(const LibGraphStorage &other);

        libGraphLoader_t loader;
        std::unique_ptr<ILibGraph> instance;
    };
}
