#ifndef ARBOL_BPLUS_H
#define ARBOL_BPLUS_H

#include "NodoBPlusBase.h"
#include "NodoBHoja.h"
#include "NodoBInterno.h"
#include "NodoGrafo.h"

class ArbolBPlus {
private:
    NodoBPlusBase* raiz;
    int orden;

    void insertarEnHoja(NodoBHoja* hoja, int clave, NodoGrafo* dato);
    void splitHoja(NodoBHoja* hoja);
    void insertarEnPadre(NodoBPlusBase* izquierda, int clave, NodoBPlusBase* derecha);
    void splitInterno(NodoBInterno* interno);
    
    NodoBInterno* encontrarPadre(NodoBPlusBase* actual, NodoBPlusBase* hijo);

public:
    ArbolBPlus(int orden);
    void insertar(int clave, NodoGrafo* dato);
    NodoGrafo* buscar(int clave, int& accesos) const;
};

#endif
