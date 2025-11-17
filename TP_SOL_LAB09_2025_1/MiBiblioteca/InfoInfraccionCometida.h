//
// Created by AlienCoders on 15/11/2025.
//

#ifndef TP_SOL_LAB09_2025_1_INFOINFRACCIONCOMETIDA_H
#define TP_SOL_LAB09_2025_1_INFOINFRACCIONCOMETIDA_H

#include "Fecha.h"
#include "InfoDeInfraccion.h"

struct InfoInfraccionCometida {
    struct Fecha fechaDeInfraccion;
    char* placa;
    struct InfoDeInfraccion infraccion;
    bool multaPagada;
    struct Fecha fechaDePago;
};

#endif //TP_SOL_LAB09_2025_1_INFOINFRACCIONCOMETIDA_H