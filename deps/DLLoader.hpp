/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** DLLoader
*/

#pragma once

#include <dlfcn.h>
#include <iostream>
#include <dlfcn.h>
#include <string>
#include "deps/Exception.hpp"

class DLLoader
{
    public:
        DLLoader(const std::string &path)
        {
            _handle = dlopen(path.c_str(), RTLD_NOW | RTLD_NODELETE);
            if (_handle == NULL) {
                throw arcade::Exception(dlerror());
            }
        }
        ~DLLoader()
        {
            dlclose(_handle);
        }
        DLLoader(const DLLoader &copy) = delete;

            DLLoader &operator=(DLLoader const &copy) = delete;

            template <typename T>
            T getsym(const std::string &name) const
            {
                return (reinterpret_cast<T>(dlsym(_handle, name.c_str())));
            }

        private:
            void *_handle;
};
