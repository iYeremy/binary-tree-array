#ifndef ARBOL_BINARIO_ARREGLO
#define ARBOL_BINARIO_ARREGLO

#include <string>
#include "cola1.h"

template <class T>
struct nodo {
    T clave;
    int id_info;
    int izq;
    int der;
    bool usado;
};

template <typename T>
struct ParRecorrido {
    T clave;
    int id_info;
};


template <typename T>
class ArbolBinarioArreglo {

private:
    nodo<T>* arbol;      
    int capacidad;       
    int raiz;            

    Cola<ParRecorrido<T>>* listInorden;
    Cola<ParRecorrido<T>>* listPreorden;
    Cola<ParRecorrido<T>>* listPosorden;

    std::string arch_arbol;
    std::string arch_info;

public:
    ArbolBinarioArreglo(int tam,
                        const std::string& archA,
                        const std::string& archI);

    void insertar(const T& clave);
    int buscarpadre(const T& clave, int pos);
    void eliminar(const T& clave);
    int buscar_nodo(const T& clave, int* padre);
    bool modificar(const T& clave, const std::string& nuevaInfo);

    int getraiz() { return arbol[0].izq; }

    void inorden(int inicio);
    void preorden(int inicio);
    void posorden(int inicio);

    bool Borrarnodo(const T& clave);

    ~ArbolBinarioArreglo() { delete[] arbol; }
};

#endif
