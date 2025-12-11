#ifndef NODO_BPLUS_BASE_H
#define NODO_BPLUS_BASE_H

class NodoBPlusBase {
protected:
    int* claves;    
    int orden;      
    bool es_hoja;   

public:
    NodoBPlusBase(int orden, bool es_hoja)
        : orden(orden), es_hoja(es_hoja)
    {
        claves = new int[orden];
    }

    virtual ~NodoBPlusBase() {
        delete[] claves;
    }

    bool esHoja() const { return es_hoja; }
};

#endif