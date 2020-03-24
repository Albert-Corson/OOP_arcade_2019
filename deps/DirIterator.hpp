/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** DirIterator
*/

#pragma once

#include <string>
#include <dirent.h>
#include "core/Exception.hpp"

class DirIterator : public std::iterator<std::input_iterator_tag, dirent *> {
    public:
        DirIterator(const std::string &path)
            : _dir(opendir(path.c_str()))
        {
            if (_dir == NULL) {
                throw arcade::Exception("Could not open dir: " + path);
            }
            ++*this;
        }
        ~DirIterator()
        {
            if (_dir != NULL)
                closedir(_dir);
        }
        DirIterator(const DirIterator &copy) = delete;

        const dirent *operator*() const
        {
            return (_file);
        }
        DirIterator &operator++()
        {
            _file = readdir(_dir);
            return (*this);
        }
        bool operator==(const DirIterator &other) const
        {
            return (this->_dir == other._dir);
        }
        bool operator!=(const DirIterator &other) const
        {
            return (!(*this == other));
        }

    private:
        DIR *_dir;
        dirent *_file;
};
