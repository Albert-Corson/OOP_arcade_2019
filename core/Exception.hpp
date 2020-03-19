/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Exception
*/

#pragma once

#include <string>
#include <exception>

class Exception : public std::exception
{
    public:
        Exception(std::string const &message)
            : _message(message)
        {
        }

        ~Exception()
        {

        }

        const char *what() const throw()
        {
            return (_message.c_str());
        }

    protected:
        const std::string &_message;
};
