cmake_minimum_required(VERSION 3.16)
project(Snakegame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "${CXX_FLAGS}")

# If you have custom cmake modules, keep this
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Find SDL3
find_package(SDL3 REQUIRED)
include_directories(${SDL3_INCLUDE_DIRS} src)

# Your sources
add_executable(Snakegame
    src/main.cpp
    src/game.cpp
    src/controller.cpp
    src/renderer.cpp
    src/snake.cpp
)



find_library(SDL_GFX_LIBRARY NAMES SDL_gfx)

if (SDL_GFX_INCLUDE_DIR AND SDL_GFX_LIBRARY)
    target_include_directories(Snakegame PRIVATE ${SDL_GFX_INCLUDE_DIR})
    target_link_libraries(Snakegame PRIVATE ${SDL_GFX_LIBRARY})
endif()

# Link SDL3
string(STRIP "${SDL3_LIBRARIES}" SDL3_LIBRARIES)
target_link_libraries(Snakegame PRIVATE ${SDL3_LIBRARIES})

# MSVC exception handling fix
if (MSVC)
    target_compile_options(Snakegame PRIVATE /EHsc /wd4514 /wd4820)
endif()
