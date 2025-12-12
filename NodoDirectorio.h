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
    ~NodoDirectorio();

    bool es_directorio() override { return true; }
    
    void agregar_hijo(int id_hijo);
    void eliminar_hijo(int id_hijo);
    void agregar_padre(int id_padre);
    void eliminar_padre(int id_padre);
    
    int* lista_hijos();
    int get_num_hijos() const { return num_hijos; }
    int* lista_padres();
    int get_num_padres() const { return num_padres; }
};
#endif