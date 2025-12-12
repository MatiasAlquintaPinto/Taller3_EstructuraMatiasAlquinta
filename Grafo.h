#ifndef GRAFO_H
#define GRAFO_H

#include <vector>

class Grafo {
private:
    int numVertices;
    std::vector<std::vector<int>> ady;

public:
    Grafo(int n);
    void agregarArista(int origen, int destino);
    const std::vector<int>& obtenerAdyacentes(int v) const;
    int getNumVertices() const;
};

#endif
