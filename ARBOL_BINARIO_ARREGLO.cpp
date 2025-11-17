#ifndef ARBOL_BINARIO_ARREGLO_CPP
#define ARBOL_BINARIO_ARREGLO_CPP

#include "ARBOL_BINARIO_ARREGLO.h"
#include <fstream>
#include <sstream>

using std::string;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::ios;

// ===================== CONSTRUCTOR =====================

template <typename T>
ArbolBinarioArreglo<T>::ArbolBinarioArreglo(int tam,
                                            const std::string& archA,
                                            const std::string& archI)
{
    capacidad = tam;
    arch_arbol = archA;
    arch_info = archI;

    arbol = new nodo<T>[capacidad + 1];

    arbol[0].izq = 0;
    arbol[0].der = 0;
    raiz = 0;

    for (int i = 1; i <= capacidad; i++) {
        arbol[i].usado = false;
        arbol[i].clave = T();
        arbol[i].id_info = 0;
        arbol[i].izq = 0;
        arbol[i].der = 0;
    }

    arbol[0].der = buscarPosLibre();
    cargarArbol(); // reconstruye si ya hay archivo
}

// ===================== BUSCAR_NODO (INTERNO) =====================

template <typename T>
int ArbolBinarioArreglo<T>::buscar_nodo(const T& clave, int* padre)
{
    int p = arbol[0].izq;
    int q = 0;

    while (p != 0) {
        if (clave == arbol[p].clave) {
            *padre = q;
            return p;
        }
        q = p;
        if (clave < arbol[p].clave)
            p = arbol[p].izq;
        else
            p = arbol[p].der;
    }

    *padre = q;
    return 0;
}

// ===================== BUSCAR PRIMERA POS. LIBRE =====================

template <typename T>
int ArbolBinarioArreglo<T>::buscarPosLibre() const
{
    for (int i = 1; i <= capacidad; i++) {
        if (!arbol[i].usado) return i;
    }
    return 0;
}

// ===================== MANEJO DE ARCHIVO INFO (INTERNO) =====================

template <typename T>
bool ArbolBinarioArreglo<T>::leerLineasInfo(std::string*& lines, int& n)
{
    ifstream in(arch_info.c_str());
    if (!in) return false;

    string linea;
    n = 0;
    while (getline(in, linea)) n++;
    in.close();

    if (n == 0) return false;

    lines = new string[n];
    ifstream in2(arch_info.c_str());
    for (int i = 0; i < n; i++) getline(in2, lines[i]);
    in2.close();
    return true;
}

template <typename T>
bool ArbolBinarioArreglo<T>::actualizarRegistroInfo(int id,
                                                    const std::string& info,
                                                    char activo)
{
    std::string* lines = nullptr;
    int n = 0;
    if (!leerLineasInfo(lines, n)) return false;

    bool ok = false;
    for (int i = 0; i < n; i++) {
        stringstream ss(lines[i]);
        int file_id;
        char sep1, activoPrev, sep2;
        ss >> file_id >> sep1 >> activoPrev >> sep2;
        if (file_id == id) {
            stringstream nueva;
            nueva << file_id << "|" << activo << "|" << info;
            lines[i] = nueva.str();
            ok = true;
            break;
        }
    }

    if (ok) {
        ofstream out(arch_info.c_str(), ios::trunc);
        if (!out) ok = false;
        else {
            for (int i = 0; i < n; i++)
                out << lines[i] << "\n";
        }
    }

    delete[] lines;
    return ok;
}

// ===================== OBTENER INFO POR ID (INTERNO) =====================

template <typename T>
bool ArbolBinarioArreglo<T>::obtenerInfoPorId(int id, std::string& info)
{
    ifstream in(arch_info.c_str());
    if (!in) return false;

    string linea;
    while (getline(in, linea)) {
        stringstream ss(linea);
        int file_id;
        char sep1, activo, sep2;
        ss >> file_id >> sep1 >> activo >> sep2;
        string resto;
        getline(ss, resto);

        if (file_id == id && activo == '1') {
            info = resto;
            return true;
        }
    }
    return false;
}

// ===================== GENERAR NUEVO ID (INTERNO) =====================

template <typename T>
int ArbolBinarioArreglo<T>::generarNuevoId()
{
    ifstream in(arch_info.c_str());
    if (!in) return 1;

    string linea;
    int ultimoId = 0;

    while (getline(in, linea)) {
        stringstream ss(linea);
        int file_id;
        char sep1, activo, sep2;
        ss >> file_id >> sep1 >> activo >> sep2;
        if (ss) ultimoId = file_id;
    }

    return ultimoId + 1;
}

// ===================== INSERTAR =====================
// Retorna false si el arreglo esta lleno.
// Escribe la informacion en arch_info como: id|1|info

template <typename T>
bool ArbolBinarioArreglo<T>::insertar(const T& clave,
                                      const std::string& infoAsociada)
{
    int padre = 0;
    int pos = buscar_nodo(clave, &padre);
    if (pos != 0) return false; // ya existe

    int nuevo = arbol[0].der;
    if (nuevo == 0 || arbol[nuevo].usado) {
        nuevo = buscarPosLibre();
        arbol[0].der = nuevo;
    }
    if (nuevo == 0) return false; // arreglo lleno

    int nuevoId = generarNuevoId();

    ofstream out(arch_info.c_str(), ios::app);
    if (!out) return false;
    out << nuevoId << "|1|" << infoAsociada << "\n";

    arbol[nuevo].clave = clave;
    arbol[nuevo].id_info = nuevoId;
    arbol[nuevo].usado = true;
    arbol[nuevo].izq = 0;
    arbol[nuevo].der = 0;

    if (arbol[0].izq == 0) {
        arbol[0].izq = nuevo;
        raiz = nuevo;
    } else {
        if (clave < arbol[padre].clave)
            arbol[padre].izq = nuevo;
        else
            arbol[padre].der = nuevo;
    }

    arbol[0].der = buscarPosLibre();
    guardarArbol();
    return true;
}

// ===================== BUSCAR =====================
// Retorna true si encuentra la clave y entrega infoEncontrada.

template <typename T>
bool ArbolBinarioArreglo<T>::buscar(const T& clave, std::string& infoEncontrada)
{
    int padre = 0;
    int pos = buscar_nodo(clave, &padre);
    if (pos == 0) return false;

    int id = arbol[pos].id_info;
    return obtenerInfoPorId(id, infoEncontrada);
}

// ===================== MODIFICAR =====================

template <typename T>
bool ArbolBinarioArreglo<T>::modificar(const T& clave,
                                       const std::string& nuevaInfo)
{
    int padre = 0;
    int pos = buscar_nodo(clave, &padre);
    if (pos == 0) return false;

    return actualizarRegistroInfo(arbol[pos].id_info, nuevaInfo, '1');
}

// ===================== ELIMINAR =====================
// Retorna false si la clave no esta.
// infoEliminada sale con la informacion asociada para que el main la imprima.
// Marca la informacion como borrada (activo = 0).

template <typename T>
bool ArbolBinarioArreglo<T>::eliminar(const T& clave,
                                      std::string& infoEliminada)
{
    int padre = 0;
    int pos = buscar_nodo(clave, &padre);
    if (pos == 0) return false;

    int id = arbol[pos].id_info;

    // Obtener info antes de marcar borrado
    obtenerInfoPorId(id, infoEliminada);

    if (!actualizarRegistroInfo(id, infoEliminada, '0'))
        return false;

    // CASOS DE ELIMINACION EN EL ARBOL

    // hoja
    if (arbol[pos].izq == 0 && arbol[pos].der == 0) {
        if (padre == 0) arbol[0].izq = 0;
        else if (arbol[padre].izq == pos) arbol[padre].izq = 0;
        else arbol[padre].der = 0;
    }
    // un hijo
    else if (arbol[pos].izq == 0 || arbol[pos].der == 0) {
        int hijo = (arbol[pos].izq != 0) ? arbol[pos].izq : arbol[pos].der;

        if (padre == 0) arbol[0].izq = hijo;
        else if (arbol[padre].izq == pos) arbol[padre].izq = hijo;
        else arbol[padre].der = hijo;
    }
    // dos hijos
    else {
        int nodoEliminar = pos;
        int hijoIzq = arbol[pos].izq;
        int hijoDer = arbol[pos].der;

        int p_suc = pos;
        int suc = arbol[pos].der;

        while (arbol[suc].izq != 0) {
            p_suc = suc;
            suc = arbol[suc].izq;
        }

        int hijoDerechoSuc = arbol[suc].der;

        if (p_suc == pos)
            arbol[pos].der = hijoDerechoSuc;
        else
            arbol[p_suc].izq = hijoDerechoSuc;

        if (padre == 0)
            arbol[0].izq = suc;
        else if (arbol[padre].izq == nodoEliminar)
            arbol[padre].izq = suc;
        else
            arbol[padre].der = suc;

        arbol[suc].izq = hijoIzq;
        arbol[suc].der = (p_suc == pos) ? arbol[pos].der : hijoDer;

        pos = nodoEliminar;
    }

    arbol[pos].usado = false;
    arbol[pos].clave = T();
    arbol[pos].id_info = 0;
    arbol[pos].izq = 0;
    arbol[pos].der = 0;

    arbol[0].der = buscarPosLibre();
    guardarArbol();
    return true;
}

// ===================== RECORRIDOS =====================
// Todos leen arch_info para llenar ParRecorrido(clave, info)

// INORDEN
template <typename T>
Cola<ParRecorrido<T>>* ArbolBinarioArreglo<T>::inorden()
{
    Cola<ParRecorrido<T>>* cola = new Cola<ParRecorrido<T>>();

    int* pila = new int[capacidad + 1];
    int top = 0;

    int actual = arbol[0].izq;

    while (actual != 0 || top > 0) {
        while (actual != 0) {
            pila[top++] = actual;
            actual = arbol[actual].izq;
        }
        actual = pila[--top];

        if (arbol[actual].usado) {
            ParRecorrido<T> p;
            p.clave = arbol[actual].clave;
            obtenerInfoPorId(arbol[actual].id_info, p.info);
            cola->InsCola(p);
        }

        actual = arbol[actual].der;
    }

    delete[] pila;
    return cola;
}

// PREORDEN
template <typename T>
Cola<ParRecorrido<T>>* ArbolBinarioArreglo<T>::preorden()
{
    Cola<ParRecorrido<T>>* cola = new Cola<ParRecorrido<T>>();

    int* pila = new int[capacidad + 1];
    int top = 0;

    int actual = arbol[0].izq;
    if (actual != 0) pila[top++] = actual;

    while (top > 0) {
        actual = pila[--top];

        if (arbol[actual].usado) {
            ParRecorrido<T> p;
            p.clave = arbol[actual].clave;
            obtenerInfoPorId(arbol[actual].id_info, p.info);
            cola->InsCola(p);
        }

        if (arbol[actual].der != 0) pila[top++] = arbol[actual].der;
        if (arbol[actual].izq != 0) pila[top++] = arbol[actual].izq;
    }

    delete[] pila;
    return cola;
}

// POSORDEN
template <typename T>
Cola<ParRecorrido<T>>* ArbolBinarioArreglo<T>::posorden()
{
    Cola<ParRecorrido<T>>* cola = new Cola<ParRecorrido<T>>();

    int* s1 = new int[capacidad + 1];
    int* s2 = new int[capacidad + 1];
    int t1 = 0, t2 = 0;

    int actual = arbol[0].izq;
    if (actual != 0) s1[t1++] = actual;

    while (t1 > 0) {
        int nodoIdx = s1[--t1];
        s2[t2++] = nodoIdx;

        if (arbol[nodoIdx].izq != 0) s1[t1++] = arbol[nodoIdx].izq;
        if (arbol[nodoIdx].der != 0) s1[t1++] = arbol[nodoIdx].der;
    }

    while (t2 > 0) {
        int idx = s2[--t2];
        if (arbol[idx].usado) {
            ParRecorrido<T> p;
            p.clave = arbol[idx].clave;
            obtenerInfoPorId(arbol[idx].id_info, p.info);
            cola->InsCola(p);
        }
    }

    delete[] s1;
    delete[] s2;
    return cola;
}

// NIVELES
template <typename T>
Cola<ParRecorrido<T>>* ArbolBinarioArreglo<T>::niveles()
{
    Cola<ParRecorrido<T>>* cola = new Cola<ParRecorrido<T>>();
    Cola<int> c;

    int r = arbol[0].izq;
    if (r != 0) c.InsCola(r);

    while (!c.ColaVacia()) {
        int idx = c.AtenderCola();

        if (arbol[idx].usado) {
            ParRecorrido<T> p;
            p.clave = arbol[idx].clave;
            obtenerInfoPorId(arbol[idx].id_info, p.info);
            cola->InsCola(p);
        }

        if (arbol[idx].izq != 0) c.InsCola(arbol[idx].izq);
        if (arbol[idx].der != 0) c.InsCola(arbol[idx].der);
    }

    return cola;
}

// ===================== GUARDAR / CARGAR ARBOL =====================

template <typename T>
void ArbolBinarioArreglo<T>::guardarArbol()
{
    ofstream out(arch_arbol.c_str(), ios::trunc);
    if (!out) return;

    out << capacidad << "\n";
    for (int i = 0; i <= capacidad; i++) {
        out << arbol[i].usado << " "
            << arbol[i].clave << " "
            << arbol[i].id_info << " "
            << arbol[i].izq << " "
            << arbol[i].der << "\n";
    }
}

template <typename T>
void ArbolBinarioArreglo<T>::cargarArbol()
{
    ifstream in(arch_arbol.c_str());
    if (!in) return;

    int cap_file;
    in >> cap_file;
    if (cap_file != capacidad) return;

    for (int i = 0; i <= capacidad; i++) {
        in >> arbol[i].usado
           >> arbol[i].clave
           >> arbol[i].id_info
           >> arbol[i].izq
           >> arbol[i].der;
    }

    raiz = arbol[0].izq;
    arbol[0].der = buscarPosLibre();
}

// ===================== DESTRUCTOR =====================

template <typename T>
ArbolBinarioArreglo<T>::~ArbolBinarioArreglo()
{
    delete[] arbol;
}

#endif
