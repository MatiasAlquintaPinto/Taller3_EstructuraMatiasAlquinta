#ifndef NODO_BPLUS_BASE_H
#define NODO_BPLUS_BASE_H

class NodoBPlusBase {
private:
    int* claves;
    int orden;
    bool es_hoja;
    int num_claves;

public:
    NodoBPlusBase(int orden, bool es_hoja);
    virtual ~NodoBPlusBase();

    bool esHoja() const;
    int getOrden() const;
    int getNumClaves() const;

    int getClave(int i) const;
    void setClave(int i, int valor);

    void aumentarNumClaves();
    void disminuirNumClaves();
};

#endif