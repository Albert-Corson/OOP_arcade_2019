/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Path
*/

#pragma once

#include <string_view>
#include <iostream>

namespace fs
{
    class Path {
        public:
            Path() noexcept
                : _str("")
            {}
            Path(const Path &other)
                : _str(other._str)
            {}
            Path(const std::string &source)
                : _str(source)
            {}
            ~Path() = default;
        
            Path &operator=(const Path &other)
            {
                _str = other._str;
                return (*this);
            }
            Path &operator=(const std::string &source)
            {
                _str = source;
                return (*this);
            }
            Path operator+(const Path &other)
            {
                return (Path(_str + other._str));
            }
            Path operator+(const std::string &source)
            {
                return (Path(_str + source));
            }
            Path operator/(const Path &other)
            {
                if (_str[_str.length() - 1] == '/')
                    _str = _str.substr(0, _str.length() - 1);
                return (Path(_str + '/' + other._str));
            }
            Path operator/(const std::string &source)
            {
                if (_str[_str.length() - 1] == '/')
                    _str = _str.substr(0, _str.length() - 1);
                return (Path(_str + '/' + source));
            }
            Path &operator+=(const Path &other)
            {
                *this = *this + other;
                return (*this);
            }
            Path &operator+=(const std::string &source)
            {
                *this = *this + source;
                return (*this);
            }
            Path &operator/=(const Path &other)
            {
                *this = *this / other;
                return (*this);
            }
            Path &operator/=(const std::string &source)
            {
                *this = *this / source;
                return (*this);
            }

            const char *c_str() const noexcept
            {
                return (_str.c_str());
            }
            bool empty() const noexcept
            {
                return (_str.empty());
            }
            bool has_parent_path() const
            {
                return (!(parent_path().empty()));
            }
            bool has_filename() const
            {
                return (!(filename().empty()));
            }
            bool has_extension() const
            {
                return (!(extension().empty()));
            }

            Path lexically_normal() const
            {
                std::string normal = _str;

                if (normal.find("./") == 0) {
                    normal = normal.substr(2);
                }
                if (normal[normal.length() - 1] == '/') {
                    normal = normal.substr(0, normal.length() - 1);
                }
                return (Path(normal));
            }
            Path lexically_relative(const std::string &base) const
            {
                return (lexically_relative(Path(base)));
            }
            Path lexically_relative(const Path &base) const
            {
                auto it_base = base.lexically_normal().begin();
                auto it_self = lexically_normal().begin();
                std::string shared("");
                std::string unique("");
                std::string relative("");

                while (!it_base.is_end() || !it_self.is_end()) {
                    if (it_base.is_end()) {
                        unique += std::string(*it_self) + "/";
                        ++it_self;
                        continue;
                    }
                    if (it_self.is_end()) {
                        relative += "../";
                        ++it_base;
                        continue;
                    }
                    if (*it_base == *it_self && relative.empty()) {
                        if (*it_base != "") {
                            shared += std::string(*it_base) + "/";
                        }
                        ++it_self;
                    } else {
                        relative += "../";
                    }
                    ++it_base;
                }
                return (Path(relative + shared + unique).lexically_normal());
            }
            Path parent_path() const
            {
                std::size_t sep_pos = _str.find_last_of("/\\");

                if (sep_pos == _str.npos) {
                    return (Path(""));
                }
                return (Path(_str.substr(0, sep_pos)));
            }
            Path filename() const
            {
                std::size_t sep_pos = _str.find_last_of("/\\");

                if (sep_pos == _str.npos) {
                    return (Path(_str));
                } else {
                    return (Path(_str.substr(sep_pos + 1)));
                }
            }
            Path stem() const
            {
                Path name = filename();
                std::size_t ext_pos = name._str.rfind('.');

                if (ext_pos == name._str.npos) {
                    ext_pos = name._str.length();
                }
                if (ext_pos == 0) {
                    return (Path(name._str));
                }
                return (Path(name._str.substr(0, ext_pos)));
            }
            Path extension() const
            {
                Path name = filename();
                std::size_t ext_pos = name._str.rfind('.');

                if (ext_pos == name._str.npos || ext_pos == 0) {
                    return (Path(""));
                }
                return (Path(name._str.substr(ext_pos)));
            }

            class iterator : std::bidirectional_iterator_tag {
                typedef iterator            it_t;
                typedef std::string_view    val_t;
                typedef std::string_view&   ref_t;

                public:
                    iterator(const Path &base)
                        : _base(base._str)
                        , _curpos(0)
                        , _view(_base.c_str(), _curpos)
                        , _is_end(false)
                        , _is_begin(true)
                    {
                    }
                    it_t operator--()
                    {
                        if (_is_end == true) {
                            _is_end = false;
                            --*this;
                        }
                        if (_curpos == 0) {
                            _is_begin = true;
                        } else {
                            std::size_t prevpos = _base.find_last_of("/\\", _curpos - 1);
                            if (prevpos == _base.npos) {
                                _view = std::string_view(_base.c_str() + _curpos);
                                _curpos = 0;
                            } else {
                                _view = std::string_view(_base.c_str() + prevpos + 1, _curpos - prevpos - 1);
                                _curpos = prevpos;
                            }
                        }
                        return (*this);
                    }
                    it_t operator--(__attribute__((unused))int)
                    {
                        it_t it = *this;

                        --*this;
                        return (it);
                    }
                    it_t operator++()
                    {
                        if (_is_begin == true) {
                            _is_begin = false;
                            ++*this;
                        }
                        if (_curpos == _base.length()) {
                            _is_end = true;
                        } else {
                            _is_begin = false;
                            std::size_t nextpos = _base.find_first_of("/\\", _curpos);
                            if (nextpos == _base.npos) {
                                _view = std::string_view(_base.c_str() + _curpos);
                                _curpos = _base.length();
                            } else {
                                _view = std::string_view(_base.c_str() + _curpos, nextpos - _curpos);
                                _curpos = nextpos + 1;
                            }
                        }
                        return (*this);
                    }
                    it_t operator++(__attribute__((unused))int)
                    {
                        it_t it = *this;

                        ++*this;
                        return (it);
                    }
                    ref_t operator*()
                    {
                        return (_view);
                    }
                    bool operator==(const it_t &other) const
                    {
                        return (_curpos == other._curpos 
                                && _is_end == other._is_end
                                && _is_begin == other._is_begin);
                    }
                    bool operator!=(const it_t &other) const
                    {
                        return (!(*this == other));
                    }
                    bool is_begin() const
                    {
                        return (_is_begin);
                    }
                    bool is_end() const
                    {
                        return (_is_end);
                    }

                private:
                    std::string _base;
                    std::size_t _curpos;
                    std::string_view _view;
                    bool _is_end;
                    bool _is_begin;
            };

            iterator begin() const
            {
                return (iterator(*this));
            }
            iterator end() const
            {
                iterator it(*this);

                while (!it.is_end()) {
                    ++it;
                }
                return (it);
            }

        private:
            std::string _str;
    };

    std::ostream &operator<<(std::ostream &os, const Path &p)
    {
        os << "\"" << p.c_str() << "\"";
        return (os);
    }
    std::istream &operator>>(std::istream &is, Path &p)
    {
        std::string buf;

        is >> buf;
        p = buf;
        return (is);
    }
}