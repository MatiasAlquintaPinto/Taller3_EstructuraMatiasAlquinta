#include "NodoArchivo.h"

NodoArchivo::NodoArchivo(int _id, int _tamaño, int _tipo)
    : NodoGrafo(_id), tamaño(_tamaño), tipo(_tipo), num_padres(0), capacidad(2)
{
    padres = new int[capacidad];
}

void NodoArchivo::agregar_padre(int id_padre) {
    if (num_padres == capacidad) {
        capacidad *= 2;
        int* nuevo = new int[capacidad];
        for (int i = 0; i < num_padres; i++) nuevo[i] = padres[i];
        delete[] padres;
        padres = nuevo;
    }
    padres[num_padres++] = id_padre;
}

void NodoArchivo::eliminar_padre(int id_padre) {
    int idx = -1;
    for (int i = 0; i < num_padres; i++) if (padres[i] == id_padre) idx = i;
    if (idx == -1) return;
    for (int i = idx; i < num_padres - 1; i++) padres[i] = padres[i + 1];
    num_padres--;
}
