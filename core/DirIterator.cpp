/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** DirIterator
*/

#include "DirIterator.hpp"
#include "Exception.hpp"

DirIterator::DirIterator(const std::string &path)
    : _dir(opendir(path.c_str()))
{
    if (_dir == NULL) {
        throw Exception("Could not open dir: " + path);
    }
    ++*this;
}

DirIterator::~DirIterator()
{
    if (_dir != NULL)
        closedir(_dir);
}

const dirent *DirIterator::operator*() const
{
    return (_file);
}

DirIterator &DirIterator::operator++()
{
    _file = readdir(_dir);
    return (*this);
}

bool DirIterator::operator==(const DirIterator &other) const
{
    return (this->_dir == other._dir);
}

bool DirIterator::operator!=(const DirIterator &other) const
{
    return (!(*this == other));
}

