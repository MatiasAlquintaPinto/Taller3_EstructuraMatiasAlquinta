#ifndef NODODIRECTORIO_H
#define NODODIRECTORIO_H

#include "NodoGrafo.h"

class NodoDirectorio : public NodoGrafo {
private:
    int* hijos;          
    int num_hijos;
    int capacidad_hijos;

    int* padres;
    int num_padres;
    int capacidad_padres;

public:
    NodoDirectorio(int _id);

    bool es_directorio() override { return true; }
    void agregar_hijo(int id_hijo);
    void eliminar_hijo(int id_hijo);
    int* lista_hijos() override { return hijos; }
    int get_num_hijos() { return num_hijos; }
    void agregar_padre(int id_padre);
    void eliminar_padre(int id_padre);
    int* lista_padres() override { return padres; }
    int get_num_padres() { return num_padres; }
};

#endif