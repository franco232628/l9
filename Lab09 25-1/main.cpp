#include <iostream>
using namespace std;

#include "Bibliotecas/Fecha.h"
#include "Bibliotecas/TablaDeInfracciones.h"
#include "Bibliotecas/InfraccionCometida.h"
#include "Bibliotecas/EmpresasRegistradas.h"
#include "Bibliotecas/funciones.h"

int main() {
    // literalmente lo mismo de antes, excepto por estas dos lineas
    struct TablaDeInfracciones *arrTablaDeInfracciones = new TablaDeInfracciones[140] {};
    struct EmpresasRegistradas *arrEmpresasRegistradas = new EmpresasRegistradas[50] {};
    int cantInfracciones=0, cantEmpresas=0;

    cargarInfracciones(arrTablaDeInfracciones, cantInfracciones);
    cargarEmpresas(arrEmpresasRegistradas, cantEmpresas);

    completarPlacas(arrEmpresasRegistradas, cantEmpresas);
    completarRegistros(arrEmpresasRegistradas, cantEmpresas, arrTablaDeInfracciones, cantInfracciones);

    calcularTotales(arrEmpresasRegistradas, cantEmpresas);
    ordenarEmpresas(arrEmpresasRegistradas, cantEmpresas);

    elaborarReporte(arrEmpresasRegistradas, cantEmpresas);

    return 0;
}