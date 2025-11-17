//
// Created by Canales Zamora on 16/11/2025.
//

#ifndef TEST17_FUNCIONES_H
#define TEST17_FUNCIONES_H

void cargarInfracciones(struct TablaDeInfracciones *arrTablaDeInfracciones, int &cantInfracciones);
void cargarEmpresas(struct EmpresasRegistradas *arrEmpresasRegistradas, int &cantEmpresas);
void completarPlacas(struct EmpresasRegistradas *arrEmpresasRegistradas, int cantEmpresas);
void completarRegistros(struct EmpresasRegistradas *arrEmpresasRegistradas, int cantEmpresas, struct TablaDeInfracciones *arrTablaDeInfracciones, int cantInfracciones);
void calcularTotales(struct EmpresasRegistradas *arrEmpresasRegistradas, int cantEmpresas);
void ordenarEmpresas(struct EmpresasRegistradas *arrEmpresasRegistradas, int cantEmpresas);
void elaborarReporte(struct EmpresasRegistradas *arrEmpresasRegistradas, int cantEmpresas);

int buscarDni(struct EmpresasRegistradas *arrEmpresasRegistradas, int dniAux, int cantEmpresas);
void agregarPlaca(struct EmpresasRegistradas &EmpresaElegida, const char *placaAux);
int buscarPlaca(struct EmpresasRegistradas *arrEmpresasRegistradas, char *placaAux, int cantEmpresas);
int buscarCodInf(struct TablaDeInfracciones *arrTablaDeInfracciones, char *codInfAux, int cantInfracciones);
void agregarInfraccion(struct EmpresasRegistradas &EmpresaElegida, const struct TablaDeInfracciones &InfraccionElegida, char *placaAux, int fechaInf, int fechaPago);
void ordenarInfracciones(struct EmpresasRegistradas &EmpresaElegida);
void imprimirEncabezadoEmpresa(ofstream &archReporte, const struct EmpresasRegistradas &EmpresaElegida, int numEmpresa);
void imprimirEncabezadoMultas(ofstream &archReporte, const char* tipo);
void imprimirMulta(ofstream &archReporte, const struct InfraccionCometida &InfraccionElegida, int numInfraccion);

void abrirInput(ifstream &arch, const char* path);
void abrirOutput(ofstream &arch, const char* path);
char* leerCadenaExacta(ifstream &arch, char delimitador);
void convertirAMayusculas(char *cadena);
void asignarCadena(char *&cadDestino, char *cadOrigen);
void asignarFecha(struct Fecha &FechaElegida, int fecha);
void cambiarEmpresa(struct EmpresasRegistradas &EmpresaI, struct EmpresasRegistradas &EmpresaJ);
void cambiarInfracciones(struct InfraccionCometida &InfraccionI, struct InfraccionCometida &InfraccionJ);
void imprimirFecha(ofstream &arch, int fecha);

#endif //TEST17_FUNCIONES_H