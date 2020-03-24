/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Exception
*/

#pragma once

#include <string>
#include <exception>

namespace arcade {
    class Exception : public std::exception {
        public:
            Exception(const std::string &message)
                : _msg(message)
            {
            }

            const char *what() const throw()
            {
                return (_msg.c_str());
            }

        protected:
            const std::string _msg;
    };
}