class NodoBInterno: public NodoBPlusBase {
private:
NodoBPlusBase** punteros; // Vector del tipo NodoBPlusBase*
// función que dado un id de NodoGrafo indica a cual Nodo del árbol B hay
// que moverse. Devuelve el índice de vector punteros.
int buscar_siguiente();
};
