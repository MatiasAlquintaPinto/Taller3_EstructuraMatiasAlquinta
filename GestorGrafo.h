#ifndef GESTORGRAFO_H
#define GESTORGRAFO_H

#include "ArbolBPlus.h"
#include "NodoArchivo.h"
#include "NodoDirectorio.h"
#include <string>
#include <vector>

class GestorGrafo {
private:
    ArbolBPlus* indice;
    int siguiente_id;
    int ultimo_accesos;
    NodoDirectorio* raiz_ptr;

public:
    GestorGrafo(int orden);
    ~GestorGrafo();

    void insertar_nodo_grafo(int clave, NodoGrafo* nodo_grafo);
    NodoGrafo* buscar_nodo_grafo(int clave);
    int get_ultimo_accesos() const;

    int crear_directorio(int id_padre);
    int crear_archivo(int id_padre, int tamaño, int tipo = 1);

    void eliminar_archivo(int id_archivo, int id_directorio_padre);

    void listar_contenido(int id_directorio);
    std::vector<std::string> obtener_rutas_completas(int id_nodo);
    int calcular_espacio_ocupado(int id_directorio);

private:
    void rutas_recursivas(int id_actual, std::vector<int>& camino, std::vector<std::string>& acum);
};

#endif