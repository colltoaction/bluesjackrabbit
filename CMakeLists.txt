cmake_minimum_required(VERSION 2.6)
project(BluesJackrabbit)
set(CMAKE_CXX_STANDARD 98)

# Optimizing
# Valgrind and debug
# Errors and warnings.
# Gtkmm
set(CMAKE_CXX_FLAGS "-O3 -DNDEBUG -ggdb -DDEBUG -fno-inline -Wall -Werror -Wextra -Wconversion -Wtype-limits -pedantic -pedantic-errors -DG_DISABLE_DEPRECATED -DGDK_DISABLE_DEPRECATED -DGDK_PIXBUF_DISABLE_DEPRECATED -DGTK_DISABLE_DEPRECATED -DGDKMM_DISABLE_DEPRECATED -DGTKMM_DISABLE_DEPRECATED")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules/")
find_package(Cppunit REQUIRED)
enable_testing()
add_subdirectory(spikes)
