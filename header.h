#ifndef HEADER_H
#define HEADER_H

#include "campo.h"
#include <QString>
#include <vector>
using std::vector;
class Header
{
    QString nombre_archivo;
    vector<Campo*> campos;
    int list_offset;
    int datos_offset;
    int longitud_registro;
public:
    Header(QString nombre, vector<Campo*> campos);
    Header(QString direccion); // leer archivo
    QString getNombre_archivo() const;
    void setNombre_archivo(const QString &value);
    vector<Campo*> getCampos() const;
    void setCampos(const vector<Campo*> &value);
    int getList_offset() const;
    void setList_offset(int value);
    int getDatos_offset() const;
    void setDatos_offset(int value);
    int getLongitud_registro();
    bool crearArchivo();
};

#endif // HEADER_H
