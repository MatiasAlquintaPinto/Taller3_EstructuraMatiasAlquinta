#include <iostream>
#include "NodoBPlusBase.h"
#include "NodoBHoja.h"
#include "NodoBInterno.h"
#include "NodoGrafo.h"

int main() {
    NodoBHoja* hoja = new NodoBHoja(4);
    hoja->setClave(0, 10);
    hoja->setDato(0, nullptr);
    hoja->aumentarNumClaves();

    std::cout << hoja->getNumClaves() << " "
              << hoja->getClave(0) << std::endl;

    NodoBInterno* interno = new NodoBInterno(4);
    interno->setClave(0, 5);
    interno->aumentarNumClaves();
    interno->setClave(1, 20);
    interno->aumentarNumClaves();

    interno->setPuntero(0, hoja);
    interno->setPuntero(1, nullptr);

    std::cout << interno->getNumClaves() << " "
              << interno->getClave(0) << " "
              << interno->buscar_siguiente(15)
              << std::endl;

    hoja->setSiguiente(nullptr);
    if (hoja->getSiguiente() == nullptr)
        std::cout << "null" << std::endl;

    delete hoja;
    delete interno;

    return 0;
}
