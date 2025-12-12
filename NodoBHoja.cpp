#include "NodoBHoja.h"

NodoBHoja::NodoBHoja(int orden)
    : NodoBPlusBase(orden, true), siguiente_hoja(nullptr)
{
    datos = new NodoGrafo*[orden];
    for (int i = 0; i < orden; ++i) datos[i] = nullptr;
}

NodoBHoja::~NodoBHoja() {
    delete[] datos;
}

NodoGrafo* NodoBHoja::getDato(int i) const {
    return datos[i];
}

void NodoBHoja::setDato(int i, NodoGrafo* d) {
    datos[i] = d;
}

NodoBHoja* NodoBHoja::getSiguiente() const {
    return siguiente_hoja;
}

void NodoBHoja::setSiguiente(NodoBHoja* s) {
    siguiente_hoja = s;
}