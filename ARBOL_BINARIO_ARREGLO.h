#ifndef ARBOL_BINARIO_ARREGLO_H
#define ARBOL_BINARIO_ARREGLO_H

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
    std::string info;
};

template <typename T>
class ArbolBinarioArreglo {
    nodo<T>* arbol;
    int capacidad;
    int raiz;

    std::string arch_arbol;
    std::string arch_info;


    int buscar_nodo(const T& clave, int* padre);
    int buscarPosLibre() const;
    bool leerLineasInfo(std::string*& lines, int& n);
    bool actualizarRegistroInfo(int id, const std::string& info, char activo);
    bool obtenerInfoPorId(int id, std::string& info);
    int generarNuevoId();

public:
    // CONSTRUCTOR
    ArbolBinarioArreglo(int tam, const std::string& archA, const std::string& archI);

    // CRUD
    bool insertar(const T& clave, const std::string& infoAsociada);
    bool buscar(const T& clave, std::string& infoEncontrada);
    bool modificar(const T& clave, const std::string& nuevaInfo);
    bool eliminar(const T& clave, std::string& infoEliminada);

    int getraiz() const { return arbol[0].izq; }

    // RECORRIDOS ITERATIVOS -- DEVUELVEN COLA
    Cola<ParRecorrido<T>>* inorden();
    Cola<ParRecorrido<T>>* preorden();
    Cola<ParRecorrido<T>>* posorden();
    Cola<ParRecorrido<T>>* niveles();

    // ARCHIVOS: GUARDAR / RECONSTRUIR
    void guardarArbol();
    void cargarArbol();

    // DESTRUCTOR
    ~ArbolBinarioArreglo();
};

#include "ARBOL_BINARIO_ARREGLO.cpp"

#endif
