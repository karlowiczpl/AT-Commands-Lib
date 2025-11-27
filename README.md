# AT-Commands-Lib

A small, lightweight C library for parsing AT-style commands and dispatching handlers. The repository provides a compact parser and a command-to-handler mapping utility that can be integrated into embedded or host applications that need to interpret AT command strings received from serial ports, modems, or similar interfaces.

## Key features
- Simple, minimal AT-command parser implemented in C.
- Mapping layer to associate AT command names with handler functions.
- Buildable with CMake.
- Designed for easy integration in embedded / serial-driven projects.

## Repository contents
- CMakeLists.txt — CMake build configuration.
- parser.h / parser.c — AT command parsing module.
- map.h / map.c — Command map / dispatch module.

## Requirements
- C compiler (gcc/clang) with C99 support (or newer).
- CMake (recommended) to configure and build the library.
- No external dependencies.

## Build (CMake)
1. Clone the repository:
   git clone https://github.com/karlowiczpl/AT-Commands-Lib.git
   cd AT-Commands-Lib

2. Create a build directory and configure:
   mkdir build && cd build
   cmake ..

3. Build the library:
   cmake --build .

4. (Optional) Install to system directories:
   sudo cmake --install .

Adjust CMake generator or toolchain if cross-compiling for embedded targets.

## Usage

Integration pattern (high-level)
1. Initialize/create a parser instance.
2. Register command handlers in the command map (associate command names with callbacks).
3. Feed incoming bytes/lines into the parser.
4. When parser recognizes a complete AT command, it looks up the handler in the map and invokes it.
5. The handler performs the requested action and typically outputs a response (e.g., "OK" / "ERROR" / custom result).

Minimal example (pseudo-C)
```c
#include "parser.h"
#include "map.h"

// Example handler signature (adapt to actual header definitions)
int example_handler(const char *params, char *response_buf, size_t response_size) {
    // process params, write to response_buf, return status code
    snprintf(response_buf, response_size, "OK");
    return 0;
}

int main(void) {
    // Create parser and map (API names below are placeholders — see headers)
    at_parser_t *parser = at_parser_create();
    at_map_t *map = at_map_create();

    // Register command "CMD" with its handler
    at_map_register(map, "CMD", example_handler);

    // Feed data into the parser (e.g. incoming from serial)
    const char *incoming = "AT+CMD=123\r\n";
    at_parser_feed(parser, incoming, strlen(incoming));

    // Parser will call the registered handler when it finds a full command

    // Cleanup
    at_parser_destroy(parser);
    at_map_destroy(map);
    return 0;
}
```

Note: Above function/type names are illustrative placeholders. Please refer to `parser.h` and `map.h` for the exact API, types, and function names.

## API overview (modules)
- parser
  - Responsibility: read a stream of bytes (or lines), detect AT commands and parameters, perform basic validation, and notify the caller (or invoke the map/dispatcher) when a complete command is available.
  - Typical functions (see parser.h):
    - Create / initialize parser object.
    - Feed bytes/data into parser.
    - Optional callbacks or return values to signal a parsed command.
    - Reset / destroy parser.

- map (dispatcher)
  - Responsibility: maintain an association between command names (e.g., "CMD", "ATZ") and C handler functions. When given a parsed command name and parameters, it calls the appropriate handler.
  - Typical functions (see map.h):
    - Create / destroy command map.
    - Register / unregister command handlers.
    - Lookup and invoke a handler for a parsed command.

Refer to `parser.h` and `map.h` for exact type signatures and usage examples.