#include "NodoBPlusBase.h"

NodoBPlusBase::NodoBPlusBase(int orden, bool es_hoja)
    : orden(orden), es_hoja(es_hoja), num_claves(0)
{
    claves = new int[orden];
    for (int i = 0; i < orden; ++i) claves[i] = -1;
}

NodoBPlusBase::~NodoBPlusBase() {
    delete[] claves;
}

bool NodoBPlusBase::esHoja() const { return es_hoja; }

int NodoBPlusBase::getOrden() const { return orden; }

int NodoBPlusBase::getNumClaves() const { return num_claves; }

int NodoBPlusBase::getClave(int i) const { return claves[i]; }

void NodoBPlusBase::setClave(int i, int valor) { claves[i] = valor; }

void NodoBPlusBase::aumentarNumClaves() { num_claves++; }

void NodoBPlusBase::disminuirNumClaves() { num_claves--; }
