#include "arbolb.h"
#include <QDebug>
#include <QtAlgorithms>

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
        }else if (l < llave_actual && !arbol->esHoja()) {
            if(existeHijo(i))
                return buscar(l,children.at(i));
        }else if ((i == children.size() - 1) && !arbol->esHoja() ) {
            if(existeHijo(i+1))
                return buscar(l,children.at(i+1));
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

bool ArbolB::insertar(Llave *l)
{
    return insertar(l,head);
}

bool ArbolB::insertar(Llave *l, ArbolB *arbol)
{
    if (arbol->esHoja()) {
        if (llaves.size() < capacidad) {
            if(llaves.size() == 0){
                llaves.append(l);
                return true;
            }
            for (int i = 0; i < llaves.size(); ++i) {
                Llave *llave_actual = llaves.at(i);
                if (l == llave_actual) {
                    llaves.insert(i, l);
                    return true;
                }else if (l < llave_actual) {
                    llaves.insert(i, l);
                    return true;
                }else if ((i == llaves.size() - 1)) {
                    llaves.append(l);
                    return true;
                }
            }
        }else{
            qDebug()<<"ya no hay espacio en la hoja, necesita hacer split";
        }
    }else{
        for (int i = 0; i < llaves.size(); ++i) {
            Llave *llave_actual = llaves.at(i);
            if (l == llave_actual) {
                if(existeHijo(i))
                    return insertar(l,children.at(i));
            }else if (l < llave_actual) {
                if(existeHijo(i))
                    return insertar(l,children.at(i));
            }else if ((i == llaves.size() - 1)) {
                if(existeHijo(i+1))
                    return insertar(l,children.at(i+1));
            }
        }
    }
    return false;
}
