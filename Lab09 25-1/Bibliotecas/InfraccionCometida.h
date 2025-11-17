//
// Created by Canales Zamora on 16/11/2025.
//

#ifndef TEST17_INFRACCIONCOMETIDA_H
#define TEST17_INFRACCIONCOMETIDA_H

struct InfraccionCometida {
    double multa;
    bool multaPagada;
    char *placa, *codigoDeLaInfraccion, *descripcion;
    struct Fecha fechaDeInfraccion, fechaDePago;
};

#endif //TEST17_INFRACCIONCOMETIDA_H