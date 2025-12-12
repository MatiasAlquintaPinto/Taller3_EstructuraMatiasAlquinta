#ifndef NODO_BINTERNO_H
#define NODO_BINTERNO_H

#include "NodoBPlusBase.h"

class NodoBInterno : public NodoBPlusBase {
private:
    NodoBPlusBase** punteros;

public:
    NodoBInterno(int orden);
    ~NodoBInterno();

    NodoBPlusBase* getPuntero(int i) const;
    void setPuntero(int i, NodoBPlusBase* p);

    int buscar_siguiente(int clave);
};

#endif
