#include "NodoBInterno.h"

NodoBInterno::NodoBInterno(int orden)
    : NodoBPlusBase(orden, false)
{
    punteros = new NodoBPlusBase*[orden + 1];
    for (int i = 0; i <= orden; ++i) punteros[i] = nullptr;
}

NodoBInterno::~NodoBInterno() {
    delete[] punteros;
}

NodoBPlusBase* NodoBInterno::getPuntero(int i) const {
    return punteros[i];
}

void NodoBInterno::setPuntero(int i, NodoBPlusBase* p) {
    punteros[i] = p;
}

int NodoBInterno::buscar_siguiente(int clave) {
    int i = 0;
    while (i < getNumClaves() && clave >= getClave(i)) {
        i++;
    }
    return i;
}
