/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** SDLWrapper
*/

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

namespace SDL {
    template<typename T>
    class Wrapper
    {
        public:
            virtual ~Wrapper()
            {};
            Wrapper(const T &) = delete;

            virtual T &operator=(const T &) = delete;
            virtual T *operator*() const
            {
                return (_value);
            }

        protected:
            Wrapper() = default;
            Wrapper(T *value)
                : _value(value)
            {}
            T *_value{NULL};
    };

    class Window : public Wrapper<SDL_Window>
    {
        public:
            Window()
            {}
            Window(const std::string &title, int x, int y, int w, int h, Uint32 flags)
            {
                this->create(title, x, y, w, h, flags);
            }
            ~Window() override
            {
                if (_renderer != NULL)
                    SDL_DestroyRenderer(_renderer);
                if (_value != NULL)
                    SDL_DestroyWindow(_value);
            }

            void create(const std::string &title, int x, int y, int w, int h, Uint32 flags)
            {
                if (_renderer != NULL)
                    SDL_DestroyRenderer(_renderer);
                if (_value != NULL)
                    SDL_DestroyWindow(_value);
                _value = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
                _renderer = SDL_CreateRenderer(_value, -1, SDL_RENDERER_ACCELERATED);
            }
            SDL_Renderer *getRenderer() const
            {
                return (_renderer);
            }
            int clear()
            {
                return (SDL_RenderClear(_renderer));
            }
            void refresh()
            {
                SDL_RenderPresent(_renderer);
            }
        
        private:
            SDL_Renderer *_renderer{NULL};
    };

    class Surface : public Wrapper<SDL_Surface>
    {
        public:
            Surface()
            {}
            Surface(SDL_Surface *surface)
                : Wrapper(surface)
            {}
            Surface(const std::string &path)
            {
                this->loadFromFile(path);
            }
            ~Surface() override
            {
                if (_value != NULL)
                    SDL_FreeSurface(_value);
            }

            bool loadFromFile(const std::string &path)
            {
                if (_value != NULL)
                    SDL_FreeSurface(_value);
                _value = IMG_Load(path.c_str());
                if (_value == NULL)
                    return (false);
                return (true);
            }
    };

    class Image : public Wrapper<SDL_Texture>
    {
        public:
            Image()
            {}
            Image(SDL_Renderer *renderer, SDL_Surface *surface)
            {
                this->loadFromSurface(renderer, surface);
            }
            Image(SDL_Renderer *renderer, const std::string &path)
            {
                this->loadFromFile(renderer, path);
            }
            ~Image() override
            {
                if (_value != NULL)
                    SDL_DestroyTexture(_value);
            }

            bool loadFromSurface(SDL_Renderer *renderer, SDL_Surface *surface)
            {
                _renderer = renderer;
                if (_value != NULL)
                    SDL_DestroyTexture(_value);
                _bounds.w = surface->w;
                _bounds.h = surface->h;
                _value = SDL_CreateTextureFromSurface(renderer, surface);
                if (_value == NULL)
                    return (false);
                return (true);
            }
            bool loadFromFile(SDL_Renderer *renderer, const std::string &path)
            {
                SDL::Surface surface(path);

                return (this->loadFromSurface(renderer, *surface));
            }
            void setPosition(int x, int y)
            {
                _bounds.x = x;
                _bounds.y = y;
            }
            void setSize(int x, int y)
            {
                _bounds.w = x;
                _bounds.h = y;
            }
            const SDL_Rect &getBounds() const
            {
                return (_bounds);
            }
            int display()
            {
                return (SDL_RenderCopy(_renderer, _value, NULL, &_bounds));
            }

        private:
            SDL_Renderer *_renderer{NULL};
            SDL_Rect _bounds{0, 0, 0, 0};
    };

    class Font : public Wrapper<TTF_Font>
    {
        public:
            Font()
            {}
            Font(const std::string &path, int fontSize)
            {
                this->loadFromFile(path, fontSize);
            }
            ~Font() override
            {
                if (_value != NULL)
                    TTF_CloseFont(_value);
            }

            bool loadFromFile(const std::string &path, int fontSize)
            {
                if (_value != NULL)
                    TTF_CloseFont(_value);
                _value = TTF_OpenFont(path.c_str(), fontSize);
                if (_value == NULL)
                    return (false);
                return (true);
            }
    };

    class Text : public SDL::Image
    {
        public:
            Text(SDL_Renderer *renderer, TTF_Font *font, const std::string &text, SDL_Color color = {255, 255, 255, 255})
                : Image(renderer, TTF_RenderText_Solid(font, text.c_str(), color))
            {}
    };
}