#include "arbolb.h"

ArbolB::ArbolB(QString path, int registro_size, int llave_size, int orden):
    path(path), registro_size(registro_size), llave_size(llave_size),orden(orden)
{
    parent = nullptr;
    head = this;
    capacidad = orden - 1;
    rrn_size = registro_size - llave_size;
}

Llave *ArbolB::buscar(Llave *l)
{
    return buscar(l,head);
}

Llave *ArbolB::buscar(Llave *l, ArbolB *arbol)
{
    for (int i = 0; i < llaves.size(); ++i) {
        Llave *llave_actual = llaves.at(i);
        if (l == llave_actual) {
            return llave_actual;
        }else if (l < llave_actual && !arbol->esHoja() && existeHijo(i)) {
            return buscar(l,children.at(i));
        }else if (!arbol->esHoja() ) {

        }
    }
    return nullptr;
}

bool ArbolB::existeHijo(int posicion) const
{
    if(posicion > children.size() - 1)
        return false;
    return true;
}

bool ArbolB::esHoja() const
{
    if (children.size() > 0) {
        return false;
    }
    return true;
}
