# const-map

Compile-time key-value table with a linear lookup.

Part of [integra-lib](https://gitlab.integrasources.com/internal-projects/integra-lib).
Header-only C++20, no exceptions, no RTTI.

## Use it

```bash
git submodule add ../const-map.git external/integra/const-map
```

```cmake
add_subdirectory(external/integra/const-map)
target_link_libraries(app PRIVATE Integra::const_map)
```

```cpp
#include <integra/const_map.hpp>
```

## Develop it

```bash
cmake -S . -B build && cmake --build build -j && ctest --test-dir build
```

Tests are built only when this repository is the top-level project, so a consumer
never builds them. Style and pipeline come from the `ci-shared` submodule; run
`git submodule update --init` before `pre-commit`.
