cmake_minimum_required (VERSION 2.8)
project (GameSFML)

# Options de compilateur
set(CMAKE_CXX_FLAGS "-std=c++14 ${CMAKE_CXX_FLAGS} -g -Wall")

# Mettre les binaires dans bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_MODULE_PATH "cmake/Modules" "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

include_directories(include)

# SFML
find_package(SFML REQUIRED system window graphics network audio)

add_subdirectory(src)

