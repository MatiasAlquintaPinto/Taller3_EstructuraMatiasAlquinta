#include "GestorGrafo.h"
#include <queue>
#include <algorithm>
#include <iostream>
#include <string>

GestorGrafo::GestorGrafo(int orden) {
    indice = new ArbolBPlus(orden);
    siguiente_id = 0;
    ultimo_accesos = 0;
    NodoDirectorio* raiz = new NodoDirectorio(siguiente_id++);
    insertar_nodo_grafo(raiz->get_id(), raiz);
    raiz_ptr = raiz;
}

GestorGrafo::~GestorGrafo() {
    delete indice;
}

void GestorGrafo::insertar_nodo_grafo(int clave, NodoGrafo* nodo_grafo) {
    indice->insertar(clave, nodo_grafo);
}

NodoGrafo* GestorGrafo::buscar_nodo_grafo(int clave) {
    int accesos = 0;
    NodoGrafo* res = indice->buscar(clave, accesos);
    ultimo_accesos = accesos;
    return res;
}

int GestorGrafo::get_ultimo_accesos() const {
    return ultimo_accesos;
}

int GestorGrafo::crear_directorio(int id_padre) {
    NodoGrafo* padre = (id_padre == 0) ? raiz_ptr : buscar_nodo_grafo(id_padre);
    if (!padre || !padre->es_directorio()) return -1;
    int nuevo_id = siguiente_id++;
    NodoDirectorio* nuevo = new NodoDirectorio(nuevo_id);
    insertar_nodo_grafo(nuevo_id, nuevo);
    NodoDirectorio* nd = dynamic_cast<NodoDirectorio*>(padre);
    nd->agregar_hijo(nuevo_id);
    nuevo->agregar_padre(id_padre);
    
    return nuevo_id;
}

int GestorGrafo::crear_archivo(int id_directorio, int tamaño, int tipo) {
    NodoGrafo* nodo_dir = (id_directorio == 0) ? raiz_ptr : buscar_nodo_grafo(id_directorio);
    if (!nodo_dir || !nodo_dir->es_directorio()) return -1;
    int nuevo_id = siguiente_id++;
    NodoArchivo* nuevo = new NodoArchivo(nuevo_id, tamaño, tipo);
    insertar_nodo_grafo(nuevo_id, nuevo);
    NodoDirectorio* nd = dynamic_cast<NodoDirectorio*>(nodo_dir);
    nd->agregar_hijo(nuevo_id); 
    nuevo->agregar_padre(id_directorio);

    return nuevo_id;
}

void GestorGrafo::eliminar_archivo(int id_archivo, int id_directorio_padre) {
    NodoGrafo* nodo = buscar_nodo_grafo(id_archivo);
    if (!nodo) return;
    NodoArchivo* archivo = dynamic_cast<NodoArchivo*>(nodo);
    if (!archivo) return;
    archivo->eliminar_padre(id_directorio_padre);
    NodoGrafo* padre = (id_directorio_padre == 0) ? raiz_ptr : buscar_nodo_grafo(id_directorio_padre);
    if (padre && padre->es_directorio()) {
        NodoDirectorio* nd = dynamic_cast<NodoDirectorio*>(padre);
        nd->eliminar_hijo(id_archivo);
    }
    if (archivo->get_num_padres() == 0) delete archivo;
}

void GestorGrafo::listar_contenido(int id_directorio) {
    NodoGrafo* nodo = (id_directorio == 0) ? raiz_ptr : buscar_nodo_grafo(id_directorio);
    if (!nodo || !nodo->es_directorio()) { std::cout << "Directorio no encontrado\n"; return; }
    NodoDirectorio* dir = dynamic_cast<NodoDirectorio*>(nodo);
    int n = dir->get_num_hijos();
    int* hijos = dir->lista_hijos();
    for (int i = 0; i < n; i++) {
        NodoGrafo* hijo = buscar_nodo_grafo(hijos[i]);
        if (hijo) std::cout << (hijo->es_directorio() ? "D " : "F ") << hijo->get_id() << "\n";
        else std::cout << "?? " << hijos[i] << "\n";
    }
    if (hijos != nullptr) delete[] hijos;
}

void GestorGrafo::rutas_recursivas(int id_actual, std::vector<int>& camino, std::vector<std::string>& acum) {
    NodoGrafo* n = (id_actual == 0) ? raiz_ptr : buscar_nodo_grafo(id_actual);
    if (!n) return;
    if (!n->es_directorio()) {
        std::string ruta = "";
        for (int x : camino) ruta += "/" + std::to_string(x);
        ruta += "/" + std::to_string(id_actual);
        acum.push_back(ruta);
        return;
    }
    NodoDirectorio* nd = dynamic_cast<NodoDirectorio*>(n);
    int np = nd->get_num_padres();
    int* padres = nd->lista_padres();
    if (np == 0) {
        std::string ruta = "";
        for (int x : camino) ruta += "/" + std::to_string(x);
        ruta += "/" + std::to_string(id_actual);
        acum.push_back(ruta);
        if (padres != nullptr) delete[] padres;
        return;
    }
    for (int i = 0; i < np; i++) {
        camino.push_back(padres[i]);
        rutas_recursivas(padres[i], camino, acum);
        camino.pop_back();
    }
    if (padres != nullptr) delete[] padres;
}

std::vector<std::string> GestorGrafo::obtener_rutas_completas(int id_archivo) {
    std::vector<std::string> resultado;
    NodoGrafo* nodo = (id_archivo == 0) ? raiz_ptr : buscar_nodo_grafo(id_archivo);
    if (!nodo) return resultado;
    int np = 0;
    int* padres = nullptr;
    NodoArchivo* na = dynamic_cast<NodoArchivo*>(nodo);
    if (na) { np = na->get_num_padres(); padres = na->lista_padres(); }
    else { 
        NodoDirectorio* nd = dynamic_cast<NodoDirectorio*>(nodo); 
        if (nd) { np = nd->get_num_padres(); padres = nd->lista_padres(); } 
    }
    
    if (np == 0) { 
        if (padres != nullptr) delete[] padres; 
        resultado.push_back("/" + std::to_string(id_archivo)); 
        return resultado; 
    }
    
    for (int i = 0; i < np; i++) {
        std::vector<int> camino;
        camino.push_back(padres[i]);
        rutas_recursivas(padres[i], camino, resultado);
    }
    
    if (padres != nullptr) delete[] padres;

    for (size_t i = 0; i < resultado.size(); i++) resultado[i] += "/" + std::to_string(id_archivo);
    
    if (resultado.empty()) resultado.push_back("/" + std::to_string(id_archivo));
    
    return resultado;
}

int GestorGrafo::calcular_espacio_ocupado(int id_directorio) {
    NodoGrafo* nodo = (id_directorio == 0) ? raiz_ptr : buscar_nodo_grafo(id_directorio);
    
    if (!nodo || !nodo->es_directorio()) {
        return 0;
    }

    NodoDirectorio* dir = dynamic_cast<NodoDirectorio*>(nodo);
    int total = 0;
    int nh = dir->get_num_hijos();
    int* hijos = dir->lista_hijos();
    
    for (int i = 0; i < nh; i++) {
        int id_hijo = hijos[i];
        
        NodoGrafo* hijo = buscar_nodo_grafo(id_hijo); 
        
        if (!hijo) {
            continue;
        }

        if (hijo->es_directorio()) {
            int espacio_dir = calcular_espacio_ocupado(id_hijo);
            total += espacio_dir;
        } else {
            NodoArchivo* archivo = dynamic_cast<NodoArchivo*>(hijo);
            if (archivo) {
                int tamaño = archivo->get_tamaño();
                total += tamaño;
            }
        }
    }
    
    if (hijos != nullptr) delete[] hijos;
    
    return total;
}