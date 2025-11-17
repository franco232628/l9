cmake_minimum_required(VERSION 4.0)
project(TP_SOL_LAB09_2025_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(TP_SOL_LAB09_2025_1 main.cpp
        MiBiblioteca/Fecha.h
        MiBiblioteca/InfoDeInfraccion.h
        MiBiblioteca/InfoInfraccionCometida.h
        MiBiblioteca/Empresa.h
        MiBiblioteca/FuncionesAux.cpp
        MiBiblioteca/FuncionesAux.h)
