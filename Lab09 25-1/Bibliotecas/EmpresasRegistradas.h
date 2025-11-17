//
// Created by Canales Zamora on 16/11/2025.
//

#ifndef TEST17_EMPRESASREGISTRADAS_H
#define TEST17_EMPRESASREGISTRADAS_H

struct EmpresasRegistradas {
    int dni, numPlacas, cantidadDeInfracciones;
    double totalPagado, totalAdeudado;
    char *nombre, *distrito,
            *placas[20]; // valor aproximado por intuicion
    struct InfraccionCometida *infraccion;
};

#endif //TEST17_EMPRESASREGISTRADAS_H