//
// Created by AlienCoders on 15/11/2025.
//

#include "FuncionesAux.h"

void LeerInfoDeInfracciones(struct InfoDeInfraccion *arrInfoInfracciones, int &cantInfoDeInfracciones) {
    ifstream archTablaInfra("ArchivosLectura/TablaDeInfracciones.csv", ios::in);
    if (not archTablaInfra.is_open()) {
        cout<<"ERROR";
        exit(1);
    }

    int i=0;
    while (true) {
        arrInfoInfracciones[i].codigo = leerCadenaExacta(archTablaInfra, ',');
        if (arrInfoInfracciones[i].codigo == nullptr) break;
        archTablaInfra>>arrInfoInfracciones[i].multa;
        archTablaInfra.get();
        arrInfoInfracciones[i].descripcion = leerCadenaExacta(archTablaInfra, '\n');
        i++;
    }
    cantInfoDeInfracciones = i;
}


void LeerEmpresas(struct Empresa *arrEmpresas, int &cantEmpresas) {
    ifstream archEmpresas("ArchivosLectura/EmpresasRegistradas.csv", ios::in);
    if (not archEmpresas.is_open()) {
        cout<<"ERROR";
        exit(1);
    }

    int i=0;
    while (true) {
        archEmpresas>>arrEmpresas[i].dni;
        if (archEmpresas.eof()) break;
        archEmpresas.get();
        arrEmpresas[i].nombre = leerCadenaExacta(archEmpresas, ',');
        arrEmpresas[i].distrito = leerCadenaExacta(archEmpresas, '\n');

        arrEmpresas[i].numPlacas = 0;
        arrEmpresas[i].infracciones = new struct InfoInfraccionCometida[40];
        arrEmpresas[i].cantidadDeInfraccions = 0;
        arrEmpresas[i].totalAdeudado = 0;
        arrEmpresas[i].totalPagado = 0;

        i++;
    }
    cantEmpresas = i;
}

void LeerPlacasRegistradas(struct Empresa *arrEmpresas, int cantEmpresas) {
    ifstream archPlacas("ArchivosLectura/PlacasRegistradas.csv", ios::in);
    if (not archPlacas.is_open()) {
        cout<<"ERROR";
        exit(1);
    }

    int dni;
    char placa[10], c;
    while (true) {
        archPlacas>>dni>>c>>placa;
        if (archPlacas.eof()) break;

        int indiceEmpresa = BuscarIndiceEmpresa(dni, arrEmpresas, cantEmpresas);
        if (indiceEmpresa>=0) {
            int k = arrEmpresas[indiceEmpresa].numPlacas;
            arrEmpresas[indiceEmpresa].placas[k] = asignarCadena(placa);
            arrEmpresas[indiceEmpresa].numPlacas++;
        }
    }
}

int BuscarIndiceEmpresa(int dni, struct Empresa *arrEmpresas, int cantEmpresas) {
    for (int i = 0; i < cantEmpresas; i++) {
        if (arrEmpresas[i].dni == dni) {
            return i;
        }
    }
    return -1;
}

void LeerInfraccionesCometidas(struct Empresa *arrEmpresas, int cantEmpresas,
                    struct InfoDeInfraccion *arrInfoInfracciones, int cantInfoDeInfracciones) {
    ifstream archInfraCome("ArchivosLectura/InfraccionesCometidas.csv", ios::in);
    if (not archInfraCome.is_open()) {
        cout<<"ERROR";
        exit(1);
    }

    int diaInfra, mesInfra, anioInfra, diaPago, mesPago, anioPago;
    char c, placa[10], codInfra[10], pago;
    while (true) {
        archInfraCome>>diaInfra>>c>>mesInfra>>c>>anioInfra>>c;
        if (archInfraCome.eof()) break;
        archInfraCome.getline(placa, 10, ',');
        archInfraCome.getline(codInfra, 10, ',');
        archInfraCome>>pago;
        if (pago=='P') archInfraCome>>c>>diaPago>>c>>mesPago>>c>>anioPago;

        int indiceEmpresa = BuscarIndiceEmpresa(placa, arrEmpresas, cantEmpresas);
        if (indiceEmpresa>=0) {

            int indiceInfraccion = BuscarIndiceInfraccion(codInfra, arrInfoInfracciones, cantInfoDeInfracciones);
            agregaInfraccion(arrEmpresas[indiceEmpresa], arrInfoInfracciones[indiceInfraccion],
                            diaInfra, mesInfra, anioInfra, diaPago, mesPago, anioPago, pago, placa);

        }


    }
    cout<<"fin";
}

int BuscarIndiceEmpresa(char* placa, struct Empresa *arrEmpresas, int cantEmpresas) {
    for (int i=0; i < cantEmpresas; i++) {
        for (int k=0 ; k<arrEmpresas[i].numPlacas; k++) {
            if ( strcmp(arrEmpresas[i].placas[k], placa) == 0 ) {
                return i;
            }
        }
    }
    return -1;
}

int BuscarIndiceInfraccion(char *codInfra,  struct InfoDeInfraccion *arrInfoInfracciones, int cantInfoDeInfracciones) {
    for (int i=0 ; i<cantInfoDeInfracciones; i++) {
        if ( strcmp(codInfra, arrInfoInfracciones[i].codigo)==0) {
            return i;
        }
    }
    return -1;
}

void agregaInfraccion(struct Empresa &empresa, struct InfoDeInfraccion infraccion,
                      int diaInfra, int mesInfra, int anioInfra,
                      int diaPago, int mesPago, int anioPago, char pago, char* placa) {

    int i = empresa.cantidadDeInfraccions;
    empresa.infracciones[i].placa = asignarCadena(placa);
    empresa.infracciones[i].infraccion = infraccion;
    empresa.infracciones[i].fechaDeInfraccion = {diaInfra, mesInfra, anioInfra, anioInfra*10000+mesInfra*100+diaInfra};
    empresa.infracciones[i].multaPagada = pago=='P';
    if (pago=='P') {
        empresa.infracciones[i].fechaDePago = {diaPago, mesPago, anioPago, anioPago*10000+mesPago*100+diaPago};
        empresa.totalPagado += infraccion.multa;
    }else {
        empresa.totalAdeudado += infraccion.multa;
    }

    empresa.cantidadDeInfraccions++;
}






char* leerCadenaExacta(ifstream &arch, char delim) {
    char cadena[1000], *pt;
    arch.getline(cadena, 1000, delim);
    if (arch.eof()) return nullptr;
    pt = new char[strlen(cadena)+1];
    strcpy(pt, cadena);
    return pt;
}

char* asignarCadena(const char* buff) {
    char *cadena = new char[strlen(buff)+1];
    strcpy(cadena, buff);
    return cadena;
}

void imprimirCadenaGrande(char *cadena) {
    for (int i=0 ; i<30 ; i++) {
        cout<<cadena[i];
    }
    cout<<"..."<<"  ";
}










