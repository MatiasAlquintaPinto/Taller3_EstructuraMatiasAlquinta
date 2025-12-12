#ifndef NODO_BHOJA_H
#define NODO_BHOJA_H

#include "NodoBPlusBase.h"
#include "NodoGrafo.h"

class NodoBHoja : public NodoBPlusBase {
private:
    NodoGrafo** datos;
    NodoBHoja* siguiente_hoja;

public:
    NodoBHoja(int orden);
    ~NodoBHoja();

    NodoGrafo* getDato(int i) const;
    void setDato(int i, NodoGrafo* d);

    NodoBHoja* getSiguiente() const;
    void setSiguiente(NodoBHoja* s);
};

#endif
