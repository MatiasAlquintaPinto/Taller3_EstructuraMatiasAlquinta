#include "ArbolBPlus.h"
#include <iostream>

ArbolBPlus::ArbolBPlus(int orden)
    : orden(orden)
{
    raiz = new NodoBHoja(orden);
}

void ArbolBPlus::insertar(int clave, NodoGrafo* dato) {
    NodoBPlusBase* nodo = raiz;
    while (!nodo->esHoja()) {
        NodoBInterno* interno = (NodoBInterno*) nodo;
        int idx = interno->buscar_siguiente(clave);
        nodo = interno->getPuntero(idx);
    }
    NodoBHoja* hoja = (NodoBHoja*) nodo;
    insertarEnHoja(hoja, clave, dato);
    if (hoja->getNumClaves() == orden) splitHoja(hoja);
}

void ArbolBPlus::insertarEnHoja(NodoBHoja* hoja, int clave, NodoGrafo* dato) {
    int n = hoja->getNumClaves();
    int i = 0;
    while (i < n && clave > hoja->getClave(i)) i++;
    for (int j = n; j > i; j--) {
        hoja->setClave(j, hoja->getClave(j - 1));
        hoja->setDato(j, hoja->getDato(j - 1));
    }
    hoja->setClave(i, clave);
    hoja->setDato(i, dato);
    hoja->aumentarNumClaves();
}

void ArbolBPlus::splitHoja(NodoBHoja* hoja) {
    int mid = orden / 2;
    NodoBHoja* nueva = new NodoBHoja(orden);
    int total = hoja->getNumClaves();
    int idxNueva = 0;
    for (int i = mid; i < total; i++) {
        nueva->setClave(idxNueva, hoja->getClave(i));
        nueva->setDato(idxNueva, hoja->getDato(i));
        idxNueva++;
    }
    nueva->setSiguiente(hoja->getSiguiente());
    hoja->setSiguiente(nueva);
    for (int i = mid; i < total; i++) {
        hoja->setClave(i, -1);
        hoja->disminuirNumClaves();
    }
    int clavePromovida = nueva->getClave(0);
    insertarEnPadre(hoja, clavePromovida, nueva);
}

NodoBInterno* ArbolBPlus::encontrarPadre(NodoBPlusBase* actual, NodoBPlusBase* hijo) {
    if (actual->esHoja()) return nullptr;
    NodoBInterno* interno = (NodoBInterno*) actual;
    int nc = interno->getNumClaves();
    for (int i = 0; i <= nc; i++) {
        NodoBPlusBase* pun = interno->getPuntero(i);
        if (pun == hijo) return interno;
    }
    for (int i = 0; i <= nc; i++) {
        NodoBPlusBase* pun = interno->getPuntero(i);
        NodoBInterno* resp = encontrarPadre(pun, hijo);
        if (resp != nullptr) return resp;
    }
    return nullptr;
}

void ArbolBPlus::insertarEnPadre(NodoBPlusBase* izquierda, int clave, NodoBPlusBase* derecha) {
    if (raiz == izquierda) {
        NodoBInterno* nuevaRaiz = new NodoBInterno(orden);
        nuevaRaiz->setClave(0, clave);
        nuevaRaiz->aumentarNumClaves();
        nuevaRaiz->setPuntero(0, izquierda);
        nuevaRaiz->setPuntero(1, derecha);
        raiz = nuevaRaiz;
        return;
    }
    NodoBInterno* padre = encontrarPadre(raiz, izquierda);
    int pos = 0;
    while (pos < padre->getNumClaves() && padre->getClave(pos) < clave) pos++;
    
    for (int j = padre->getNumClaves(); j > pos; j--) padre->setClave(j, padre->getClave(j - 1));
    
    for (int j = padre->getNumClaves(); j > pos; j--) padre->setPuntero(j + 1, padre->getPuntero(j));
    
    padre->setClave(pos, clave);
    padre->setPuntero(pos + 1, derecha);
    padre->aumentarNumClaves();
    if (padre->getNumClaves() == orden) splitInterno(padre);
}

void ArbolBPlus::splitInterno(NodoBInterno* interno) {
    int mid = orden / 2;
    NodoBInterno* nueva = new NodoBInterno(orden);
    int nc = interno->getNumClaves();
    int idxNueva = 0;
    for (int i = mid + 1; i < nc; i++) {
        nueva->setClave(idxNueva, interno->getClave(i));
        nueva->setPuntero(idxNueva, interno->getPuntero(i));
        nueva->aumentarNumClaves();
        idxNueva++;
    }
    nueva->setPuntero(idxNueva, interno->getPuntero(nc));
    int clavePromovida = interno->getClave(mid);
    for (int i = mid; i < nc; i++) {
        interno->setClave(i, -1);
        interno->setPuntero(i + 1, nullptr);
        interno->disminuirNumClaves();
    }
    insertarEnPadre(interno, clavePromovida, nueva);
}

NodoGrafo* ArbolBPlus::buscar(int clave, int& accesos) const {
    accesos = 0;
    NodoBPlusBase* nodo = raiz;
    while (!nodo->esHoja()) {
        NodoBInterno* interno = (NodoBInterno*) nodo;
        int idx = interno->buscar_siguiente(clave);
        nodo = interno->getPuntero(idx);
        accesos++;
    }
    NodoBHoja* hoja = (NodoBHoja*) nodo;
    int n = hoja->getNumClaves();
    for (int i = 0; i < n; i++) {
        accesos++;
        if (hoja->getClave(i) == clave) return hoja->getDato(i);
    }
    return nullptr;
}