#include <iostream>
#include "GestorGrafo.h"

int main() {
    int orden = 4; 
    GestorGrafo gestor(orden);
    int opcion = -1;
    while (opcion != 0) {
        std::cout << "\nQue quieres hacer?\n";
        std::cout << "1. Crear un nuevo directorio\n";
        std::cout << "2. Crear un archivo\n";
        std::cout << "3. Listar contenido de un directorio\n";
        std::cout << "4. Obtener rutas de un archivo/directorio\n";
        std::cout << "5. Calcular espacio ocupado en un directorio\n";
        std::cout << "6. Eliminar un archivo\n";
        std::cout << "0. Salir\n";
        std::cout << "Elige una opcion: ";
        std::cin >> opcion;

        if (opcion == 1) {
            int id_padre;
            std::cout << "En que directorio quieres crear el nuevo directorio? (ID): ";
            std::cin >> id_padre;
            int nuevo_id = gestor.crear_directorio(id_padre);
            if (nuevo_id != -1) std::cout << "Directorio creado con ID: " << nuevo_id << "\n";
            else std::cout << "ID padre invalido\n";
        }

        else if (opcion == 2) {
            int id_dir, tamaño, tipo;
            std::cout << "En que directorio quieres crear el archivo? (ID): ";
            std::cin >> id_dir;
            std::cout << "Tamaño del archivo en bytes: ";
            std::cin >> tamaño;
            std::cout << "Tipo de archivo (1 default): ";
            std::cin >> tipo;
            int nuevo_id = gestor.crear_archivo(id_dir, tamaño, tipo);
            if (nuevo_id != -1) std::cout << "Archivo creado con ID: " << nuevo_id << "\n";
            else std::cout << "Directorio invalido\n";
        }

        else if (opcion == 3) {
            int id_dir;
            std::cout << "De que directorio quieres ver el contenido? (ID): ";
            std::cin >> id_dir;
            gestor.listar_contenido(id_dir);
        }

        else if (opcion == 4) {
            int id_nodo;
            std::cout << "De que archivo/directorio quieres obtener las rutas? (ID): ";
            std::cin >> id_nodo;
            auto rutas = gestor.obtener_rutas_completas(id_nodo);
            for (const auto& r : rutas) std::cout << r << "\n";
        }

        else if (opcion == 5) {

            int id_dir;
            std::cout << "De que directorio quieres calcular el espacio ocupado? (ID): ";
            std::cin >> id_dir;
            int espacio = gestor.calcular_espacio_ocupado(id_dir);
            std::cout << "Espacio ocupado: " << espacio << " bytes\n";
        }

        else if (opcion == 6) {
            int id_arch, id_padre;
            std::cout << "ID del archivo a eliminar: ";
            std::cin >> id_arch;
            std::cout << "ID del directorio padre: ";
            std::cin >> id_padre;
            gestor.eliminar_archivo(id_arch, id_padre);
            std::cout << "Archivo eliminado si existía\n";
        }

        else if (opcion == 0) std::cout << "Saliendo\n";
        else std::cout << "Opcion invalida\n";
    }

    return 0;
}
