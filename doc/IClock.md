# [IClock](../core/IClock.hpp)

The `Clock` is a helper class inheriting from [`IClock`](../core/IClock.hpp).

It implements two methods:

``` c++
// Returns the elapsed time in milliseconds from the internal time stamp to now
long IClock::getElapsedTime() = 0;

// Reset the internal time stamp to the current time
void IClock::reset();
```
