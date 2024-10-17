cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_COMPILER "mpicxx")

project(MPI_Rect_Rule VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(DBG_BUILD ON CACHE BOOL "For using debug flags during build.")

if (DBG_BUILD)
    add_compile_options(-Wall -Wextra -Wpedantic -Werror -g -Og)
else ()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror -O2)
endif ()

enable_testing()
add_subdirectory(src)
