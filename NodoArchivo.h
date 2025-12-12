#ifndef NODOARCHIVO_H
#define NODOARCHIVO_H
#include "NodoGrafo.h"

class NodoArchivo : public NodoGrafo {
private:
    int tamaño;
    int tipo;
    int* padres;
    int num_padres;
    int capacidad;

public:
    NodoArchivo(int _id, int _tamaño, int _tipo);
    bool es_directorio() override { return false; }
    void agregar_padre(int id_padre);
    void eliminar_padre(int id_padre);
    int* lista_padres() override { return padres; }
    int get_num_padres() { return num_padres; }
    int get_tamaño() { return tamaño; }
};
#endif
