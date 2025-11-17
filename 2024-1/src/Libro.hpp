//
// Created by alulab14 on 17/11/2025.
//

#ifndef INC_2024_1_LIBRO_HPP
#define INC_2024_1_LIBRO_HPP

#include "Venta.hpp"

struct Libro {
    char *codigo;
    char *titulo;
    char *autor;
    double precio;
    struct Venta *ventas;
    int librosVendidos;
    int sumaDeCalificaciones;
    int ranking;
};



#endif //INC_2024_1_LIBRO_HPP