/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** DirIterator
*/

#pragma once

#include <string>
#include <dirent.h>

class DirIterator : public std::iterator<std::input_iterator_tag, dirent *> {
    public:
        DirIterator(const std::string &path);
        ~DirIterator();

        const dirent *operator*() const;
        DirIterator &operator++();
        bool operator==(const DirIterator &other) const;
        bool operator!=(const DirIterator &other) const;

    private:
        DIR *_dir;
        dirent *_file;
};
