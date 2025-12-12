#include "Grafo.h"

Grafo::Grafo(int n) {
    numVertices = n;
    ady.resize(n);
}

void Grafo::agregarArista(int origen, int destino) {
    if (origen >= 0 && origen < numVertices && destino >= 0 && destino < numVertices) {
        ady[origen].push_back(destino);
    }
}

const std::vector<int>& Grafo::obtenerAdyacentes(int v) const {
    return ady[v];
}

int Grafo::getNumVertices() const {
    return numVertices;
}
