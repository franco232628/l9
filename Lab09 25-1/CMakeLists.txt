cmake_minimum_required(VERSION 4.0)
project(test17)

set(CMAKE_CXX_STANDARD 20)

add_executable(test17 main.cpp
        Bibliotecas/Fecha.h
        Bibliotecas/TablaDeInfracciones.h
        Bibliotecas/InfraccionCometida.h
        Bibliotecas/EmpresasRegistradas.h
        Bibliotecas/funciones.cpp
        Bibliotecas/funciones.h)
