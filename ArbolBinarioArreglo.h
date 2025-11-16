#ifndef ARBOL_BINARIO_ARREGLO
#define ARBOL_BINARIO_ARREGLO

#include <string>

template <class T>
struct nodo{
    T clave;
    int izq;
    int der;
    bool usado;
};

#endif