//
// Created by alulab14 on 17/11/2025.
//

#ifndef INC_2024_1_AUXILIARYFUNCTIONS_HPP
#define INC_2024_1_AUXILIARYFUNCTIONS_HPP

#include "Utils.hpp"

void leerClientes(struct Cliente *cliente, int &cantClientes, const char *file_name);

void open_read(ifstream &input, const char *file_name);

char *read_str(ifstream &input, char delim);

void leerLibro(struct Libro *arrLibros, int &cantLibro, const char *file_name);

double read_double(ifstream &input);

void leerVentas(struct Libro *arrLibros, int cantLibro, struct Cliente *arrClientes,
                int cantClientes, const char *file_name);

int read_int( ifstream & input);
int read_date( ifstream & input);
int buscarLibro(struct Libro * arrLibros, int cantLibro, char * codigo_leido);
int buscarCliente(struct Cliente * arrClientes, int cantClientes, int dni_leido);

// void agregarVenta(Libro & lib, int dni,
//     int fecha, int calificacion);


void asignarFecha(struct Fecha &fecha, int fecha1);
void imprimirDebug(struct Libro *arrLibros, int cantLibros,
                   struct Cliente *arrClientes, int cantClientes);
void cambiarS( struct Libro & cat1,  struct Libro & cat2);

#endif //INC_2024_1_AUXILIARYFUNCTIONS_HPP
