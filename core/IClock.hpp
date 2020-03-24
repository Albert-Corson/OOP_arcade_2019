/*
** EPITECH PROJECT, 2019
** arcade
** File description:
** iclock
*/

#ifndef ICLOCK_HPP_
#define ICLOCK_HPP_

namespace arcade {
    class IClock {
        public:
            virtual ~IClock() = default;

            virtual void reset() = 0;
            virtual long getElapsedNanoseconds() const noexcept = 0;
            virtual long getElapsedMicroseconds() const noexcept = 0;
            virtual long getElapsedMilliseconds() const noexcept = 0;
            virtual long getElapsedSeconds() const noexcept = 0;

        protected:
            IClock() = default;
    };
}

#endif
