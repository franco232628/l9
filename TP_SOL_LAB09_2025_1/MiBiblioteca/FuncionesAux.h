//
// Created by AlienCoders on 15/11/2025.
//

#ifndef TP_SOL_LAB09_2025_1_FUNCIONESAUX_H
#define TP_SOL_LAB09_2025_1_FUNCIONESAUX_H

#include <iostream>
#include <fstream>
using namespace std;
#include<cstring>
#include<iomanip>

#include "Fecha.h"
#include "InfoDeInfraccion.h"
#include "InfoInfraccionCometida.h"
#include "Empresa.h"

char* leerCadenaExacta(ifstream &arch, char delim) ;
char* asignarCadena(const char* buff);
int BuscarIndiceEmpresa(int dni, struct Empresa *arrEmpresas, int cantEmpresas) ;
int BuscarIndiceEmpresa(char* placa, struct Empresa *arrEmpresas, int cantEmpresas);
int BuscarIndiceInfraccion(char *codInfra,  struct InfoDeInfraccion *arrInfoInfracciones, int cantInfoDeInfracciones);

void LeerInfoDeInfracciones(struct InfoDeInfraccion *arrInfoInfracciones, int &cantInfoDeInfracciones);
void LeerEmpresas(struct Empresa *arrEmpresas, int &cantEmpresas) ;
void LeerPlacasRegistradas(struct Empresa *arrEmpresas, int cantEmpresas) ;
void LeerInfraccionesCometidas(struct Empresa *arrEmpresas, int cantEmpresas, struct InfoDeInfraccion *arrInfoInfracciones, int cantInfoDeInfracciones);
void agregaInfraccion(struct Empresa &empresa, struct InfoDeInfraccion infraccion,
                      int diaInfra, int mesInfra, int anioInfra,
                      int diaPago, int mesPago, int anioPago, char pago, char* placa);



void imprimirCadenaGrande(char *cadena);

#endif //TP_SOL_LAB09_2025_1_FUNCIONESAUX_H