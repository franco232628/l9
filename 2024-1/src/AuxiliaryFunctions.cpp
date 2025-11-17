//
// Created by alulab14 on 17/11/2025.
//

#include "AuxiliaryFunctions.hpp"




void open_read(ifstream &input, const char *file_name) {
    input.open(file_name, ios::in);
    if (!input.is_open()) {
        cout << "Error opening file " << file_name << endl;
        exit(1);
    }
}

char * read_str(ifstream &input, char delim) {
    char *str, buffer[90];
    input >> ws;
    input.getline(buffer, 90, delim);
    if (input.eof()) return nullptr;
    str = new char[strlen(buffer) + 1];
    strcpy(str, buffer);
    return str;
}



double read_double(ifstream &input) {
    double num;
    input >> num;
    input.get();
    return num;
}
int read_int(ifstream &input) {
    int num;
    input >> num;
    input.get();
    return num;
}

int read_date(ifstream &input) {
    int dd, mm, anio;
    char c;
    input >> dd >> c >> mm >> c >> anio;
    return dd + mm*100 + anio*10000;
}

int buscarLibro(struct Libro *arrLibros, int cantLibro, char *codigo_leido) {
    for (int i = 0; i < cantLibro; i++) {
        if (strcmp(codigo_leido, arrLibros[i].codigo) == 0) {
            return i;
        }
    }
    return -1;
}

int buscarCliente(struct Cliente *arrClientes, int cantClientes, int dni_leido) {
    for (int i = 0; i < cantClientes; i++) {
        if (dni_leido == arrClientes[i].dni) {
            return i;
        }
    }
    return -1;
}



void leerClientes(struct Cliente *arrClientes, int &cantClientes, const char *file_name) {
    ifstream input;
    open_read(input, file_name);
    while (true) {
        // 54393647,Reyes Tang Edward
        input>>arrClientes[cantClientes].dni;
        if (input.eof()) break;
        input.get();
        arrClientes[cantClientes].nombre = read_str(input,'\n');
        cantClientes++;
    }
}


void leerLibro(struct Libro *arrLibros, int &cantLibro, const char *file_name) {
    ifstream input;
    open_read(input, file_name);

    while (true) {
        // IIM5175,Diamantes y pedernales,Jose Maria Arguedas,69.02
        arrLibros[cantLibro].codigo = read_str(input,',');
        if (input.eof()) break;
        arrLibros[cantLibro].titulo = read_str(input,',');
        arrLibros[cantLibro].autor = read_str(input,',');
        arrLibros[cantLibro].precio = read_double(input);

        arrLibros[cantLibro].ventas = new Venta[10];
        arrLibros[cantLibro].librosVendidos = 0;
        arrLibros[cantLibro].sumaDeCalificaciones = 0;
        arrLibros[cantLibro].ranking= 0;
        cantLibro++;
    }
}




void leerVentas(struct Libro *arrLibros, int cantLibro, struct Cliente *arrClientes, int cantClientes,
                const char *file_name) {
    ifstream input;
    open_read(input, file_name);
    char *codigo_leido;
    int dni_leido, fecha_leida, calificacion_leida;
    while (true) {
        //CRY6839,34460612,15/10/2023,93
        codigo_leido = read_str(input,',');
        if (input.eof()) break;
        dni_leido = read_int(input);
        fecha_leida = read_date(input);
        input.get();
        input>>calificacion_leida;
        int posLibro = buscarLibro(arrLibros, cantLibro, codigo_leido);
        int posCliente = buscarCliente(arrClientes, cantClientes, dni_leido);
        if (posLibro != -1 && posCliente != -1) {//arrLibros[i].librosVendidos
            // agregarVenta( arrLibros[posLibro], dni_leido,fecha_leida, calificacion_leida);
            arrLibros[posLibro].ventas[arrLibros[posLibro].librosVendidos].dni = dni_leido;
            arrLibros[posLibro].ventas[arrLibros[posLibro].librosVendidos].calificacion = calificacion_leida;
            asignarFecha(arrLibros[posLibro].ventas[arrLibros[posLibro].librosVendidos].fecha,fecha_leida);
            arrLibros[posLibro].sumaDeCalificaciones += calificacion_leida;
            arrLibros[posLibro].librosVendidos ++;
        }
    }
    for (int i = 0; i < cantLibro; i++) {
        if (arrLibros[i].librosVendidos != 0) {
            double condicionRanking = arrLibros[i].sumaDeCalificaciones/double(arrLibros[i].librosVendidos);
            if (condicionRanking < 25) {
                arrLibros[i].ranking = 1;
            }else {
                if (condicionRanking < 50) {
                    arrLibros[i].ranking = 2;
                }else {
                    if (condicionRanking < 75) {
                        arrLibros[i].ranking = 3;
                    }else arrLibros[i].ranking = 5;
                }
            }
        }else {
            arrLibros[i].ranking = 0;
        }
    }

    for (int i = 0; i < cantLibro-1; i++) {
        for (int j = i+1; j < cantLibro; j++) {
            // if (strcmp(arrLibros[i].titulo, arrLibros[j].titulo) >0) {
            //     cambiarS(arrLibros[i], arrLibros[j]);
            // }
            // if (arrLibros[i].ranking < arrLibros[j].ranking) {
            //     cambiarS(arrLibros[i], arrLibros[j]);
            // }
            if (strcmp(arrLibros[i].titulo, arrLibros[j].titulo) >0 or arrLibros[i].ranking < arrLibros[j].ranking) {
                cambiarS(arrLibros[i], arrLibros[j]);
            }
        }
    }
}
void cambiarS( struct Libro & cat1,  struct Libro & cat2) {
    struct Libro temp;
    temp = cat1;
    cat1 = cat2;
    cat2 = temp;
}

// void agregarVenta(Libro &lib, int dni, int fecha, int calificacion) {
//     if (lib.librosVendidos < 10 ) {
//         lib.ventas[lib.librosVendidos].dni = dni;
//         lib.ventas[lib.librosVendidos].calificacion = calificacion;
//         asignarFecha(lib.ventas[lib.librosVendidos].fecha, fecha);
//         lib.sumaDeCalificaciones += calificacion;
//         lib.librosVendidos++;
//     }
// }

void asignarFecha(struct Fecha &fecha, int fecha1) {
    fecha.fecha = fecha1;
    fecha.aa = fecha1/10000;
    fecha.mm = (fecha1/100)%100;
    fecha.dd = fecha1%100;
}


void imprimirDebug(struct Libro *arrLibros, int cantLibros,
                   struct Cliente *arrClientes, int cantClientes) {

    cout << "===== DEBUG DE LIBROS, CLIENTES Y VENTAS =====\n\n";

    for (int i = 0; i < cantLibros; i++) {

        cout << "Libro #" << i+1 << endl;
        cout << "  Codigo: " << arrLibros[i].codigo << endl;
        cout << "  Titulo: " << arrLibros[i].titulo << endl;
        cout << "  Autor : " << arrLibros[i].autor << endl;
        cout << "  Precio: " << arrLibros[i].precio << endl;
        cout << "  Ranking: " << arrLibros[i].ranking << endl;
        cout << "  Ventas registradas: " << arrLibros[i].librosVendidos << endl;

        // imprimir ventas del libro
        if (arrLibros[i].librosVendidos == 0) {
            cout << "    (No tiene ventas)\n\n";
            continue;
        }

        cout << "    --- Ventas ---\n";
        for (int j = 0; j < arrLibros[i].librosVendidos; j++) {


            // buscar cliente para su nombre
            int posCliente = buscarCliente(arrClientes, cantClientes, arrLibros[i].ventas[j].dni);

            cout << "    Venta " << j+1 << endl;
            cout << "      DNI: " << arrLibros[i].ventas[j].dni << endl;

            if (posCliente != -1)
                cout << "      Cliente: " << arrClientes[posCliente].nombre << endl;
            else
                cout << "      Cliente: (NO ENCONTRADO)" << endl;

            cout << "      Fecha: "
                 << arrLibros[i].ventas[j].fecha.dd << "/"
                 << arrLibros[i].ventas[j].fecha.mm << "/"
                 << arrLibros[i].ventas[j].fecha.aa << endl;

            cout << "      Calificacion: " << arrLibros[i].ventas[j].calificacion << endl;
            cout << endl;
        }

        cout << "------------------------------------------\n\n";
    }
}
