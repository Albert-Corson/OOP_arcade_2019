# [KeyState](../deps/keys.hpp)

`KeyState` is a simple structure that stores the state of a key.

See all available key IDs [here](../deps/keys.hpp).

```c++
struct KeyState {
    KeyState(Key keyID) : key{keyID} {};
    ~KeyState() = default;

    Key key;                // The is of the key
    bool is_pressed{false}; // Represents the state
};
```