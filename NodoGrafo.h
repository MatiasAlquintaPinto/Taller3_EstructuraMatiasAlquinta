#ifndef NODOGRAFO_H
#define NODOGRAFO_H

class NodoGrafo {
protected:
    int id;

public:
    NodoGrafo(int _id) : id(_id) {}
    int get_id() { return id; }

    virtual bool es_directorio() = 0;
    virtual int* lista_padres() { return nullptr; }
    virtual int* lista_hijos() { return nullptr; }
};

#endif