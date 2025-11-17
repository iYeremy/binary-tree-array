#include <iostream>
#include <string>
#include "ARBOL_BINARIO_ARREGLO.h"

using namespace std;

void imprimirCola(Cola<ParRecorrido<string>>* c)
{
    while (!c->ColaVacia()) {
        ParRecorrido<string> p = c->AtenderCola();
        cout << "Clave: " << p.clave
             << " | Info: " << p.info << "\n";
    }
}

int main() 
{
    ArbolBinarioArreglo<string> arbol(
        20,              // capacidad del árbol
        "arbol.txt",     // archivo del árbol
        "info.txt"       // archivo con info asociada
    );

    cout << "\n==== INSERTAR CLAVES ====\n";
    while (true) {
        string clave;
        cout << "\nIngrese clave (o 'fin'): ";
        cin >> clave;
        if (clave == "fin") break;

        cin.ignore();
        string info;
        cout << "Ingrese informacion asociada: ";
        getline(cin, info);

        if (arbol.insertar(clave, info))
            cout << "Insertado correctamente.\n";
        else
            cout << "No se pudo insertar (duplicado o árbol lleno).\n";
    }

    cout << "\n==== RECORRIDOS INICIALES ====\n";

    cout << "\nInorden:\n";
    imprimirCola(arbol.inorden());

    cout << "\nPreorden:\n";
    imprimirCola(arbol.preorden());

    cout << "\nPosorden:\n";
    imprimirCola(arbol.posorden());

    cout << "\nPor niveles:\n";
    imprimirCola(arbol.niveles());

    // ==============================
    // === MENU DE BUSCAR/ELIMINAR ==
    // ==============================

    while (true) {
        cout << "\n===== MENU =====\n";
        cout << "1. Buscar\n";
        cout << "2. Eliminar\n";
        cout << "3. Salir del menu\n";
        cout << "Seleccione opcion: ";

        int op;
        cin >> op;

        if (op == 1) {
            string clave;
            cout << "Clave a buscar: ";
            cin >> clave;

            string info;
            if (arbol.buscar(clave, info))
                cout << "ENCONTRADO: " << info << "\n";
            else
                cout << "No existe esa clave.\n";
        }
        else if (op == 2) {
            string clave;
            cout << "Clave a eliminar: ";
            cin >> clave;

            string infoEliminada;
            if (arbol.eliminar(clave, infoEliminada))
                cout << "Eliminado. Info asociada:\n" << infoEliminada << "\n";
            else
                cout << "No existe esa clave.\n";
        }
        else if (op == 3) {
            break;
        }
        else {
            cout << "Opcion invalida.\n";
        }
    }

    cout << "\n==== RECORRIDOS FINALES ====\n";

    cout << "\nInorden:\n";
    imprimirCola(arbol.inorden());

    cout << "\nPreorden:\n";
    imprimirCola(arbol.preorden());

    cout << "\nPosorden:\n";
    imprimirCola(arbol.posorden());

    cout << "\nPor niveles:\n";
    imprimirCola(arbol.niveles());

    cout << "\nPrograma finalizado. Se guardó el árbol.\n";
    return 0;
}
