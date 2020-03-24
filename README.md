
# Key Management
- `IGame`
    - `Game`
        - asks event to `Core`

- `Core`
    - asks event to `ILibGraph`

- `ILibGraph`
    - Sends events
    - `LibGraph`
        - Sends events

- `Core`
    - receives event from `ILibGraph`
    - checks key to change the lib (game /graph)
    - sends event back to the `IGame`

- `IGame`
    - `Game`
        - receives event from `Core`



# Resource (Image / Audio)

Each resource has a `type`. Each resource has `2 filepath` one for the `graph` and the other for the `ascii`.

An empty filepath will return `true` for a call to `loadResource`.

Resource type
```
            +---> Audio 
    Type ---|
            +---- Image
```

- `Core`:
    - stores resource path
    
        `core.hpp`
        ```c++
        std::unordered_map<int, Resource>

        void loadResource(std::unordered_map<int, Resource>& resources);
        ```

- `ILibGraph`:
    - `LibGraph`:
        - Store resource with an id

- `IGame`
    - `Game`
        - when launch, loads resource into the `core`
