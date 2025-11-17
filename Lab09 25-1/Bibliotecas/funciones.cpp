#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;

#include "Fecha.h"
#include "TablaDeInfracciones.h"
#include "InfraccionCometida.h"
#include "EmpresasRegistradas.h"
#include "funciones.h"
#define ANCHO 240

void cargarInfracciones(struct TablaDeInfracciones *arrTablaDeInfracciones, int &cantInfracciones) {
    ifstream archInfracciones;
    abrirInput(archInfracciones, "ArchivosDeDatos/TablaDeInfracciones_Lab09.csv");

    // M1046,658.70,Obstruir la ciclovia
    while (true) {
        arrTablaDeInfracciones[cantInfracciones].codigo = leerCadenaExacta(archInfracciones, ',');
        if (arrTablaDeInfracciones[cantInfracciones].codigo == nullptr) break;

        archInfracciones >> arrTablaDeInfracciones[cantInfracciones].multa;
        archInfracciones.get();
        arrTablaDeInfracciones[cantInfracciones].descripcion = leerCadenaExacta(archInfracciones, '\n');

        convertirAMayusculas(arrTablaDeInfracciones[cantInfracciones].codigo);
        convertirAMayusculas(arrTablaDeInfracciones[cantInfracciones].descripcion);
        cantInfracciones++;
    }
}

void cargarEmpresas(struct EmpresasRegistradas *arrEmpresasRegistradas, int &cantEmpresas) {
    ifstream archEmpresas;
    abrirInput(archEmpresas, "ArchivosDeDatos/EmpresasRegistradas_Lab09.csv");

    // 47844324,vilca lee nestor hugo,Comas
    while (true) {
        archEmpresas >> arrEmpresasRegistradas[cantEmpresas].dni;
        if (archEmpresas.eof()) break;

        archEmpresas.get();
        arrEmpresasRegistradas[cantEmpresas].nombre = leerCadenaExacta(archEmpresas, ',');
        arrEmpresasRegistradas[cantEmpresas].distrito = leerCadenaExacta(archEmpresas, '\n');

        convertirAMayusculas(arrEmpresasRegistradas[cantEmpresas].nombre);
        convertirAMayusculas(arrEmpresasRegistradas[cantEmpresas].distrito);
        cantEmpresas++;
    }
}

void completarPlacas(struct EmpresasRegistradas *arrEmpresasRegistradas, int cantEmpresas) {
    ifstream archPlacas;
    abrirInput(archPlacas, "ArchivosDeDatos/PlacasRegistradas_Lab09.csv");

    int dniAux, posEmpresa;
    char *placaAux;

    // 12270502,G855-340
    while (true) {
        archPlacas >> dniAux;
        if (archPlacas.eof()) break;

        archPlacas.get();
        placaAux = leerCadenaExacta(archPlacas, '\n'); // se pudo inicializar esta cadena en 10 y leerla con "arch >>" pero el enunciado no deja

        posEmpresa = buscarDni(arrEmpresasRegistradas, dniAux, cantEmpresas);
        if (posEmpresa != -1) {
            agregarPlaca(arrEmpresasRegistradas[posEmpresa], placaAux); // no use agregarCadena por temas de intuitividad

            // asignarCadena(arrEmpresasRegistradas[posEmpresa].placas[arrEmpresasRegistradas[posEmpresa].numPlacas], placaAux);
            // arrEmpresasRegistradas[posEmpresa].numPlacas++;
            // delete placaAux;
        }
    }
}

void completarRegistros(struct EmpresasRegistradas *arrEmpresasRegistradas, int cantEmpresas, struct TablaDeInfracciones *arrTablaDeInfracciones, int cantInfracciones) {
    ifstream archRegistros;
    abrirInput(archRegistros, "ArchivosDeDatos/InfraccionesCometidas_Lab09.csv");

    int dia, mes, anho, fechaInf, fechaPago,
         posEmpresa, posInfraccion;
    char *placaAux, *codInfAux,
            c; // caracter multiusos

    // 18/12/2024,G938-342,G2061,P,26/1/2025
    while (true) {
        archRegistros >> dia;
        if (archRegistros.eof()) break;

        archRegistros >> c >> mes >> c >> anho >> c;
        fechaInf = anho*10000 + mes*100 + dia;

        placaAux = leerCadenaExacta(archRegistros, ',');
        codInfAux = leerCadenaExacta(archRegistros, ',');
        if (archRegistros.get() == 'P') {
            archRegistros >> c >> dia >> c >> mes >> c >> anho;
            fechaPago = anho*10000 + mes*100 + dia;
        }
        else fechaPago = 0;

        posEmpresa = buscarPlaca(arrEmpresasRegistradas, placaAux, cantEmpresas);
        posInfraccion = buscarCodInf(arrTablaDeInfracciones, codInfAux, cantInfracciones);
        if (posEmpresa != -1 && posInfraccion != -1) {
            agregarInfraccion(arrEmpresasRegistradas[posEmpresa], arrTablaDeInfracciones[posInfraccion], placaAux, fechaInf, fechaPago);
        }
        // añadido opcional
        delete placaAux;
        delete codInfAux;
    }
}

void calcularTotales(struct EmpresasRegistradas *arrEmpresasRegistradas, int cantEmpresas) {
    for (int i=0; i < cantEmpresas; i++) { // para cada empresa
        for (int j=0; j < arrEmpresasRegistradas[i].cantidadDeInfracciones; j++) { // para cada infraccion de una empresa
            if (arrEmpresasRegistradas[i].infraccion[j].multaPagada) {
                arrEmpresasRegistradas[i].totalPagado += arrEmpresasRegistradas[i].infraccion[j].multa;
            }
            else arrEmpresasRegistradas[i].totalAdeudado += arrEmpresasRegistradas[i].infraccion[j].multa;
        }
    }
}

void ordenarEmpresas(struct EmpresasRegistradas *arrEmpresasRegistradas, int cantEmpresas) {
    for (int i=0; i < cantEmpresas; i++) { // no le puse cantEmpresas-1 ya que aprovecharemos este bucle al ordenar infracciones (no afecta en nada al ordenar empresas)
        for (int j=i+1; j < cantEmpresas; j++) {
            if (strcmp(arrEmpresasRegistradas[i].distrito, arrEmpresasRegistradas[j].distrito) > 0)
                cambiarEmpresa(arrEmpresasRegistradas[i], arrEmpresasRegistradas[j]);
        }

        ordenarInfracciones(arrEmpresasRegistradas[i]);
    }
}

void elaborarReporte(struct EmpresasRegistradas *arrEmpresasRegistradas, int cantEmpresas) {
    ofstream archReporte;
    abrirOutput(archReporte, "ArchivosDeReporte/reporte.txt");
    archReporte << setprecision(2) << fixed;

    int j, posAdeudadas;

    archReporte << setw(130) << "MINISTERIO DE TRANSPORTES" << endl;
    archReporte << setw(135) << "LISTADO DE INFRACCIONES POR EMPRESA" << endl;

    for (int i=0; i < cantEmpresas; i++) {
        imprimirEncabezadoEmpresa(archReporte, arrEmpresasRegistradas[i], i+1);

        // me pase un poco con los if
        if (arrEmpresasRegistradas[i].cantidadDeInfracciones > 0) { // si la empresa tiene infracciones
            posAdeudadas=0; // posicion en la que empiezan las multas no pagadas

            if (arrEmpresasRegistradas[i].infraccion[0].multaPagada) { // si hay infracciones pagadas
                imprimirEncabezadoMultas(archReporte, "PAGADAS");

                for (j=0; arrEmpresasRegistradas[i].infraccion[j].multaPagada && j < arrEmpresasRegistradas[i].cantidadDeInfracciones; j++) // iterando en las multas pagadas
                    imprimirMulta(archReporte, arrEmpresasRegistradas[i].infraccion[j], j+1);

                archReporte << setw(ANCHO) << setfill('=') << "" << endl << setfill(' ');
                archReporte << "  TOTAL PAGADO:   " << arrEmpresasRegistradas[i].totalPagado << endl;
                posAdeudadas = j;
            }

            if (posAdeudadas != arrEmpresasRegistradas[i].cantidadDeInfracciones) { // si aun quedan multas
                imprimirEncabezadoMultas(archReporte, "ADEUDADAS");

                for (j=posAdeudadas; j < arrEmpresasRegistradas[i].cantidadDeInfracciones; j++) // iterando en las multas siguientes (no pagadas)
                    imprimirMulta(archReporte, arrEmpresasRegistradas[i].infraccion[j], j-posAdeudadas+1);

                archReporte << setw(ANCHO) << setfill('=') << "" << endl << setfill(' ');
                archReporte << "  TOTAL ADEUDADO:   " << arrEmpresasRegistradas[i].totalAdeudado << endl;
            }
        }
    }
}

/* Funciones secundarias */

int buscarDni(struct EmpresasRegistradas *arrEmpresasRegistradas, int dniAux, int cantEmpresas) {
    for (int i=0; i < cantEmpresas; i++) {
        if (arrEmpresasRegistradas[i].dni == dniAux) return i;
    }
    return -1;
}

void agregarPlaca(struct EmpresasRegistradas &EmpresaElegida, const char *placaAux) { // agregar al final del arreglo y aumentar el numPlacas
    EmpresaElegida.placas[EmpresaElegida.numPlacas] = new char[strlen(placaAux) + 1]; // tambien puede ser new char[9] ya que todas las placas son de igual longitud
    strcpy(EmpresaElegida.placas[EmpresaElegida.numPlacas], placaAux);

    EmpresaElegida.numPlacas++;
    delete placaAux; // añadido personal para despejar el espacio que ocupaba esta copia
}

int buscarPlaca(struct EmpresasRegistradas *arrEmpresasRegistradas, char *placaAux, int cantEmpresas) {
    for (int i=0; i < cantEmpresas; i++) {
        for (int j=0; j < arrEmpresasRegistradas[i].numPlacas; j++) {
            if (strcmp(arrEmpresasRegistradas[i].placas[j], placaAux) == 0) return i;
        }
    }
    return -1;
}

int buscarCodInf(struct TablaDeInfracciones *arrTablaDeInfracciones, char *codInfAux, int cantInfracciones) {
    for (int i=0; i < cantInfracciones; i++) {
        if (strcmp(arrTablaDeInfracciones[i].codigo, codInfAux) == 0) return i;
    }
    return -1;
}

void agregarInfraccion(struct EmpresasRegistradas &EmpresaElegida, const struct TablaDeInfracciones &InfraccionElegida, char *placaAux, int fechaInf, int fechaPago) {
    if (EmpresaElegida.cantidadDeInfracciones == 0) EmpresaElegida.infraccion = new InfraccionCometida[40]; // Si es la primera infraccion, inicializamos el arreglo (numero aproximado por intuicion)

    struct InfraccionCometida *infraccionActual = &EmpresaElegida.infraccion[EmpresaElegida.cantidadDeInfracciones]; // por temas de intuitividad

    asignarCadena(infraccionActual->codigoDeLaInfraccion, InfraccionElegida.codigo); // recordar que para llamar a un campo desde un puntero de estructura se usa el operador "->"
    asignarCadena(infraccionActual->descripcion, InfraccionElegida.descripcion);
    asignarCadena(infraccionActual->placa, placaAux);
    asignarFecha(infraccionActual->fechaDeInfraccion, fechaInf);
    infraccionActual->multa = InfraccionElegida.multa;

    infraccionActual->multaPagada = fechaPago > 0;
    if (infraccionActual->multaPagada) asignarFecha(infraccionActual->fechaDePago, fechaPago);

    EmpresaElegida.cantidadDeInfracciones++;
}

void ordenarInfracciones(struct EmpresasRegistradas &EmpresaElegida) { // tambien se puede ordenar con el bubble sort de siempre, pero aqui usare menos iteraciones
    for (int i=0; i < EmpresaElegida.cantidadDeInfracciones-1; i++) {
        /*
         * como queremos poner a todas las infracciones con multaPagada = true del lado izquierdo,
         * el problema esta cuando encontramos una multa no pagada,
         * hay que buscar una que si este pagada para que ocupe su lugar
         *
         * [S, N, N, S, S, S, N, N, N, N]
         *     ^
         */
        if (!EmpresaElegida.infraccion[i].multaPagada) {

            for (int j=i+1; j < EmpresaElegida.cantidadDeInfracciones; j++) { // desde la posicion que le sigue hasta el final del arreglo
                if (EmpresaElegida.infraccion[j].multaPagada) {
                    cambiarInfracciones(EmpresaElegida.infraccion[i], EmpresaElegida.infraccion[j]);
                    // como ya hay una multa pagada en esta posicion, podemos pasar a la siguiente
                    break;
                }
                /*
                 * si todas las multas siguientes tampoco estan pagadas, el arreglo ya esta ordenado y no hay necesidad de seguir
                 * [S, S, S, S, N, N, N, N, N, N]
                 *              ^
                 */
                if (j == EmpresaElegida.cantidadDeInfracciones-1) return;
            }
        }
    }
}

void imprimirEncabezadoEmpresa(ofstream &archReporte, const struct EmpresasRegistradas &EmpresaElegida, int numEmpresa) {
    archReporte << setw(ANCHO) << setfill('=') << "" << endl << setfill(' ');

    archReporte << setw(2) << setfill('0') << numEmpresa << ")  DNI: " << setw(8) << EmpresaElegida.dni << setfill(' ');
    archReporte << left << "    NOMBRE: " << setw(40) << EmpresaElegida.nombre;
    archReporte << "DISTRITO: " << setw(20) << EmpresaElegida.distrito << "PLACAS: ";

    if (EmpresaElegida.numPlacas != 0) {
        archReporte << EmpresaElegida.placas[0];
        for (int i=1; i < EmpresaElegida.numPlacas; i++) {
            archReporte << '/' << EmpresaElegida.placas[i];
        }
    }
    else archReporte << "NO HAY PLACAS"; // imposible en este caso, pero ahi esta

    archReporte << endl << right;
}

void imprimirEncabezadoMultas(ofstream &archReporte, const char* tipo) {
    archReporte << setw(ANCHO) << setfill('=') << "" << endl << setfill(' ');
    archReporte << "  MULTAS " << tipo << ":" << endl;
    archReporte << setw(11) << "FECHA" << setw(13) << "PLACA" << setw(25) << "CODIGO DE INFRACCION" << setw(13) << "DESCRIPCION" << setw(145) << "MULTA" << setw(19);
    if (strcmp(tipo, "PAGADAS") == 0) archReporte << "FECHA DE PAGO";
    archReporte << endl << setw(ANCHO) << setfill('-') << "" << endl << setfill(' ');
}

void imprimirMulta(ofstream &archReporte, const struct InfraccionCometida &InfraccionElegida, int numInfraccion) {
    archReporte << ' ' << setfill('0') << setw(2) << numInfraccion << ")  ";

    imprimirFecha(archReporte, InfraccionElegida.fechaDeInfraccion.fecha);
    // recordar que las cadenas de caracteres se acomodan con left y los numeros con right
    archReporte << "   " << left << setw(15) << InfraccionElegida.placa << setw(17) << InfraccionElegida.codigoDeLaInfraccion << setw(150) << InfraccionElegida.descripcion;
    archReporte << right << setw(7) << InfraccionElegida.multa << setw(5) << "";

    if (InfraccionElegida.multaPagada) imprimirFecha(archReporte, InfraccionElegida.fechaDePago.fecha);
    archReporte << endl;
}

/* Funciones terciarias */

void abrirInput(ifstream &arch, const char* path) {
    arch.open(path, ios::in);
    if (!arch.is_open()) {
        cerr << "Error opening " << path << endl;
        exit(1);
    }
}

void abrirOutput(ofstream &arch, const char* path) {
    arch.open(path, ios::out);
    if (!arch.is_open()) {
        cerr << "Error opening " << path << endl;
        exit(1);
    }
}

char* leerCadenaExacta(ifstream &arch, char delimitador) {
    char aux[170], *cad;

    arch >> ws;
    arch.getline(aux, 170, delimitador);
    if (arch.eof()) return nullptr;
    arch.clear(); // opcional

    cad = new char[strlen(aux) + 1];
    strcpy(cad, aux);
    return cad;
}

void convertirAMayusculas(char *cadena) {
    for (int i=0; cadena[i]; i++) {
        cadena[i] = toupper(cadena[i]); // tambien sirve restarle 'a' - 'A' si es minuscula
    }
}

void asignarCadena(char *&cadDestino, char *cadOrigen) { // en este lab no permiten que dos punteros apunten al mismo dato
    // la cosa es copiar una cadena en otra pero asignandole su propio espacio independiente
    cadDestino = new char[strlen(cadOrigen) + 1];
    strcpy(cadDestino, cadOrigen);
}

void asignarFecha(struct Fecha &FechaElegida, int fecha) { // obligan a rellenar estos 4 campos asi que es una buena funcion para ahorrar lineas
    FechaElegida.fecha = fecha;
    FechaElegida.aa = fecha/10000;
    FechaElegida.mm = (fecha/100)%100;
    FechaElegida.dd = fecha%100;
}

void cambiarEmpresa(struct EmpresasRegistradas &EmpresaI, struct EmpresasRegistradas &EmpresaJ) {
    struct EmpresasRegistradas EmpresaAux = EmpresaI;
    EmpresaI = EmpresaJ;
    EmpresaJ = EmpresaAux;
}

void cambiarInfracciones(struct InfraccionCometida &InfraccionI, struct InfraccionCometida &InfraccionJ) {
    struct InfraccionCometida InfraccionAux = InfraccionI;
    InfraccionI = InfraccionJ;
    InfraccionJ = InfraccionAux;
}

void imprimirFecha(ofstream &arch, int fecha) {
    int anho = fecha/10000,
         mes = (fecha/100)%100,
         dia = fecha%100;

    // observar que se mantienen todas las consideraciones para que la impresion salga como se espera y no afecte a los datos que le siguen
    arch << right << setfill('0') << setw(2) << dia << '/' << setw(2) << mes << '/' << anho << setfill(' ');
}