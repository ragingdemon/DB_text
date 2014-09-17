#ifndef ARBOLB_H
#define ARBOLB_H

#include "llave.h"
#include <QString>
#include <QList>
class ArbolB
{
    QString path;
    ArbolB *parent;
    ArbolB *head;
    QList<Llave*> llaves;
    QList<ArbolB*> children;    
    int registro_size;
    int llave_size;
    int rrn_size; //se deduce con llave_size
    int orden; //capacidad para los hijos
    int capacidad; // capacidad para las llaves

    Llave *buscar(Llave *l, ArbolB *arbol);
    bool existeHijo(int posicion)const;
    bool insertar(Llave *l,ArbolB *arbol);
public:
    ArbolB(QString path, int registro_size, int llave_size, int orden);
    Llave *buscar(Llave *l);
    bool esHoja()const;
    bool insertar(Llave *l);

};

#endif // ARBOLB_H
