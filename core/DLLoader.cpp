/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** DLLoader
*/

#include <dlfcn.h>
#include <iostream>
#include "DLLoader.hpp"
#include "Exception.hpp"

DLLoader::DLLoader(const std::string &path)
{
    _handle = dlopen(path.c_str(), RTLD_NOW | RTLD_NODELETE);
    if (_handle == NULL) {
        throw Exception(dlerror());
    }
}

DLLoader::~DLLoader()
{
    dlclose(_handle);
}