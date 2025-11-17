#include "src/AuxiliaryFunctions.hpp"



int main() {
    // struct Cliente arrClientes[70];
    struct Cliente *arrClientes = new Cliente[70]{};
    int cantClientes = 0;
    leerClientes(arrClientes, cantClientes, "Data/Clientes.csv");
    // for (int i = 0; i < cantClientes; i++) {
    //     cout << arrClientes[i].dni << "   -   " << arrClientes[i].nombre << endl;
    // }


    struct Libro *arrLibros = new Libro[300]{};
    int cantLibro = 0;
    leerLibro(arrLibros, cantLibro, "Data/Libros.csv");

    // for (int i = 0; i < cantLibro; i++) {
    //     cout << arrLibros[i].codigo << "   -   " << arrLibros[i].titulo
    //     << "   -   " << arrLibros[i].autor<< "   -   " << arrLibros[i].precio << endl;
    // }

    leerVentas(arrLibros, cantLibro, arrClientes, cantClientes, "Data/Ventas.csv");
    imprimirDebug(arrLibros, cantLibro, arrClientes, cantClientes);
    return 0;
}
