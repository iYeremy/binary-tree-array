#include <iostream>
#include <string>
#include "ARBOL_BINARIO_ARREGLO.h"

using namespace std;

bool convertirCodigo(const string& entrada, long long& codigo)
{
    if (entrada.empty()) return false;
    codigo = 0;
    for (size_t i = 0; i < entrada.size(); ++i) {
        char c = entrada[i];
        if (c < '0' || c > '9') return false;
        codigo = (codigo * 10) + (c - '0');
    }
    return true;
}

bool leerCodigo(const string& prompt, long long& codigo)
{
    string texto;
    cout << prompt;
    cin >> texto;
    cin.ignore(10000, '\n');

    if (!convertirCodigo(texto, codigo)) {
        cout << "Codigo invalido. Solo digitos.\n";
        return false;
    }
    return true;
}

string capturarInfo(const string& etiquetaNombre,
                    const string& etiquetaApellido)
{
    string nombre, apellido;
    cout << etiquetaNombre;
    getline(cin, nombre);
    cout << etiquetaApellido;
    getline(cin, apellido);
    return "Nombre: " + nombre + " | Apellido: " + apellido;
}

void imprimirCola(Cola<ParRecorrido<long long>>* c)
{
    while (c && !c->ColaVacia()) {
        ParRecorrido<long long> p = c->AtenderCola();
        cout << "Clave: " << p.clave
             << " | Info: " << p.info << "\n";
    }

    delete c;
}

void mostrarRecorridos(const string& titulo,
                       ArbolBinarioArreglo<long long>& arbol)
{
    cout << "\n==== " << titulo << " ====\n";

    cout << "\nInorden:\n";
    imprimirCola(arbol.inorden());

    cout << "\nPreorden:\n";
    imprimirCola(arbol.preorden());

    cout << "\nPosorden:\n";
    imprimirCola(arbol.posorden());

    cout << "\nPor niveles:\n";
    imprimirCola(arbol.niveles());
}

int main() 
{
    ArbolBinarioArreglo<long long> arbol(
        20,              // capacidad del árbol
        "arbol.txt",     // archivo del árbol
        "info.txt"       // archivo con info asociada
    );

    cout << "\n==== REGISTRO INICIAL ====\n";
    while (true) {
        string codigoTxt;
        cout << "\nIngrese codigo (o 'fin' para terminar): ";
        cin >> codigoTxt;
        if (codigoTxt == "fin") {
            cin.ignore(10000, '\n');
            break;
        }

        long long codigo;
        if (!convertirCodigo(codigoTxt, codigo)) {
            cin.ignore(10000, '\n');
            cout << "Codigo invalido. Solo digitos.\n";
            continue;
        }

        cin.ignore(10000, '\n');
        string info = capturarInfo("Ingrese nombre: ",
                                   "Ingrese apellido: ");

        if (arbol.insertar(codigo, info))
            cout << "Insertado correctamente.\n";
        else
            cout << "No se pudo insertar (codigo duplicado o arbol lleno).\n";
    }

    mostrarRecorridos("RECORRIDOS INICIALES", arbol);

    // ==============================
    // === MENU PRINCIPAL ===========
    // ==============================

    bool salir = false;
    while (!salir) {
        cout << "\n===== MENU PRINCIPAL =====\n";
        cout << "1. Buscar por codigo\n";
        cout << "2. Modificar informacion\n";
        cout << "3. Eliminar registro\n";
        cout << "4. Insertar nuevo registro\n";
        cout << "5. Mostrar recorridos\n";
        cout << "6. Salir\n";
        cout << "Seleccione opcion: ";

        int op;
        if (!(cin >> op)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada invalida. Intente nuevamente.\n";
            continue;
        }
        cin.ignore(10000, '\n');

        if (op == 1) {
            long long codigo;
            if (!leerCodigo("Codigo a buscar: ", codigo)) continue;

            string info;
            if (arbol.buscar(codigo, info))
                cout << "ENCONTRADO: " << info << "\n";
            else
                cout << "No existe ese codigo.\n";
        }
        else if (op == 2) {
            long long codigo;
            if (!leerCodigo("Codigo a modificar: ", codigo)) continue;

            string nuevaInfo = capturarInfo("Nuevo nombre: ",
                                            "Nuevo apellido: ");

            if (arbol.modificar(codigo, nuevaInfo))
                cout << "Informacion actualizada correctamente.\n";
            else
                cout << "No se pudo modificar: codigo inexistente.\n";
        }
        else if (op == 3) {
            long long codigo;
            if (!leerCodigo("Codigo a eliminar: ", codigo)) continue;

            string infoEliminada;
            if (arbol.eliminar(codigo, infoEliminada))
                cout << "Eliminado. Info asociada:\n" << infoEliminada << "\n";
            else
                cout << "No existe ese codigo.\n";
        }
        else if (op == 4) {
            long long codigo;
            if (!leerCodigo("Ingrese codigo: ", codigo)) continue;

            string info = capturarInfo("Ingrese nombre: ",
                                       "Ingrese apellido: ");

            if (arbol.insertar(codigo, info))
                cout << "Insertado correctamente.\n";
            else
                cout << "No se pudo insertar (codigo duplicado o arbol lleno).\n";
        }
        else if (op == 5) {
            mostrarRecorridos("RECORRIDOS ACTUALES", arbol);
        }
        else if (op == 6) {
            salir = true;
        }
        else {
            cout << "Opcion invalida.\n";
        }
    }

    mostrarRecorridos("RECORRIDOS FINALES", arbol);

    cout << "\nPrograma finalizado. Se guardo el arbol.\n";
    return 0;
}
