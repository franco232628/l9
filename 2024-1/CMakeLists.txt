cmake_minimum_required(VERSION 4.0)
project(2024_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(2024_1 main.cpp
        src/AuxiliaryFunctions.cpp
        src/AuxiliaryFunctions.hpp
        src/Utils.hpp
        src/Cliente.hpp
        src/Fecha.hpp
        src/Venta.hpp
        src/Libro.hpp)
