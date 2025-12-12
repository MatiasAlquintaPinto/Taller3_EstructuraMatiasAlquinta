#include "NodoDirectorio.h"
#include <iostream>
#include <algorithm>

NodoDirectorio::NodoDirectorio(int _id)
    : NodoGrafo(_id), num_hijos(0), capacidad_hijos(4), num_padres(0), capacidad_padres(2)
{
    hijos = new int[capacidad_hijos];
    padres = new int[capacidad_padres];
}

NodoDirectorio::~NodoDirectorio() {
    delete[] hijos;
    delete[] padres;
}

void NodoDirectorio::agregar_hijo(int id_hijo) {
    if (num_hijos == capacidad_hijos) {
        capacidad_hijos *= 2;
        int* nuevo = new int[capacidad_hijos];
        for (int i = 0; i < num_hijos; i++) nuevo[i] = hijos[i];
        delete[] hijos;
        hijos = nuevo;
    }
    std::cout << "num_hijos: " << num_hijos << "\n";
    hijos[num_hijos++] = id_hijo;
}

void NodoDirectorio::eliminar_hijo(int id_hijo) {
    int idx = -1;
    for (int i = 0; i < num_hijos; i++) if (hijos[i] == id_hijo) idx = i;
    if (idx == -1) return;
    for (int i = idx; i < num_hijos - 1; i++) hijos[i] = hijos[i + 1];
    num_hijos--;
}

void NodoDirectorio::agregar_padre(int id_padre) {
    if (num_padres == capacidad_padres) {
        capacidad_padres *= 2;
        int* nuevo = new int[capacidad_padres];
        for (int i = 0; i < num_padres; i++) nuevo[i] = padres[i];
        delete[] padres;
        padres = nuevo;
    }
    padres[num_padres++] = id_padre;
}

void NodoDirectorio::eliminar_padre(int id_padre) {
    int idx = -1;
    for (int i = 0; i < num_padres; i++) if (padres[i] == id_padre) idx = i;
    if (idx == -1) return;
    for (int i = idx; i < num_padres - 1; i++) padres[i] = padres[i + 1];
    num_padres--;
}

int* NodoDirectorio::lista_hijos() {
    int* copia = new int[num_hijos];
    for (int i = 0; i < num_hijos; i++) {
        copia[i] = hijos[i];
    }
    return copia;
}

int* NodoDirectorio::lista_padres() {
    int* copia = new int[num_padres];
    for (int i = 0; i < num_padres; i++) {
        copia[i] = padres[i];
    }
    return copia;
}