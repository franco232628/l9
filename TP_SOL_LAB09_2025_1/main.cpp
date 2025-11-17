#include "MiBiblioteca/FuncionesAux.h"

int main() {

    struct InfoDeInfraccion *arrInfoInfracciones = new InfoDeInfraccion[150];
    int cantInfoDeInfracciones;
    LeerInfoDeInfracciones(arrInfoInfracciones, cantInfoDeInfracciones);

    struct Empresa *arrEmpresas = new Empresa[50];
    int cantEmpresas;
    LeerEmpresas(arrEmpresas, cantEmpresas);

    LeerPlacasRegistradas(arrEmpresas, cantEmpresas);

    LeerInfraccionesCometidas(arrEmpresas, cantEmpresas, arrInfoInfracciones, cantInfoDeInfracciones);

    for (int i=0; i < cantEmpresas; i++) {
        cout<<"EMPRESA: "<<arrEmpresas[i].dni<<endl;
        cout<<"Placas: ";
        for (int k=0 ; k<arrEmpresas[i].numPlacas ; k++) {
            cout<<arrEmpresas[i].placas[k]<<" ";
        }
        cout<<endl;

        cout<<"Infracciones Pagadas:"<<endl;
        for (int p=0 ; p<arrEmpresas[i].cantidadDeInfraccions ; p++) {
            if (arrEmpresas[i].infracciones[p].multaPagada) {
                cout<<arrEmpresas[i].infracciones[p].fechaDeInfraccion.fecha<<"  ";
                cout<<arrEmpresas[i].infracciones[p].placa<<"  ";
                cout<<arrEmpresas[i].infracciones[p].infraccion.codigo<<"  ";
                imprimirCadenaGrande(arrEmpresas[i].infracciones[p].infraccion.descripcion);
                cout<<arrEmpresas[i].infracciones[p].infraccion.multa<<"  ";
                cout<<arrEmpresas[i].infracciones[p].fechaDePago.fecha<<endl;
            }
        }
        cout<<"Total Pagado:" <<arrEmpresas[i].totalPagado<<endl;
        cout<<"_______________________________________________________________________________________________"<<endl;

        cout<<"Infracciones Adeudadas:"<<endl;
        for (int p=0 ; p<arrEmpresas[i].cantidadDeInfraccions ; p++) {
            if (arrEmpresas[i].infracciones[p].multaPagada==false) {
                cout<<arrEmpresas[i].infracciones[p].fechaDeInfraccion.fecha<<"  ";
                cout<<arrEmpresas[i].infracciones[p].placa<<"  ";
                cout<<arrEmpresas[i].infracciones[p].infraccion.codigo<<"  ";
                imprimirCadenaGrande(arrEmpresas[i].infracciones[p].infraccion.descripcion);
                cout<<arrEmpresas[i].infracciones[p].infraccion.multa<<endl;
            }
        }
        cout<<"Total Adeudado:" <<arrEmpresas[i].totalAdeudado<<endl<<endl;

    }


    return 0;
}