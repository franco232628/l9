//
// Created by AlienCoders on 15/11/2025.
//

#ifndef TP_SOL_LAB09_2025_1_EMPRESA_H
#define TP_SOL_LAB09_2025_1_EMPRESA_H

struct Empresa {
    int dni;
    char* nombre;
    char* distrito;

    char* placas[10]; // placas[i] = new
    int numPlacas;

    struct InfoInfraccionCometida *infracciones;// infraciones = new struct InfoInfraccionCometida[40]
    int cantidadDeInfraccions;

    double totalPagado;
    double totalAdeudado;
};

#endif //TP_SOL_LAB09_2025_1_EMPRESA_H