#include <cstdlib>
#include <iostream>

#ifndef COLA1_H     
#define COLA1_H 

using namespace std;

template <typename D>
struct NodoCola {
    D dato;
    NodoCola* sig;
};

template <typename D>
class Cola {
    NodoCola<D>* cab;
    NodoCola<D>* fin;

public:
    Cola() { cab = fin = nullptr; }

    void InsCola(D x) {
        NodoCola<D>* nuevo = new NodoCola<D>;
        nuevo->dato = x;
        nuevo->sig = nullptr;

        if (cab == nullptr) cab = nuevo;
        else fin->sig = nuevo;

        fin = nuevo;
    }

    D AtenderCola() {
        NodoCola<D>* aux = cab;
        D valor = aux->dato;
        cab = aux->sig;
        delete aux;
        return valor;
    }

    bool ColaVacia() {
        return cab == nullptr;
    }

    ~Cola() {
        while (cab != nullptr) {
            NodoCola<D>* aux = cab;
            cab = cab->sig;
            delete aux;
        }
    }
};


#endif
