#ifndef ARBOL_BINARIO_ARREGLO
#define ARBOL_BINARIO_ARREGLO

#include <string>
#include "cola1.h"

template <class T>
struct nodo{
    T clave;
    int izq;
    int der;
    bool usado;
};
template <typename T>
class ArbolBinarioArreglo {

private:
    nodoA<T>* arbol;
    int capacidad;
    int raiz;

    // recorridos usando cola1.h
    cola* listInorden;
    cola* listPreorden;
    cola* listPosorden;

    // archivos
    std::string arch_arbol;
    std::string arch_info;

public:
    ArbolBinarioArreglo(int tam,
                        const std::string& archA,
                        const std::string& archI);

    void insertar(const T& clave);         // igual al profe (void insertar)
    int buscarpadre(const T& clave,int pos);
    void eliminar(const T& clave);         // igual al profe (void eliminar)
    int buscar_nodo(const T& clave,int* p);
    int getraiz(){ return arbol[0].izq; }  // igualito al profe

    void inorden(int inicio);
    void preorden(int inicio);
    void posorden(int inicio);

    bool Borrarnodo(const T& clave);
    ~ArbolBinarioArreglo(){ delete arbol; }
};

#endif