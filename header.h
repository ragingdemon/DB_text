#ifndef HEADER_H
#define HEADER_H

#include "campo.h"
#include <string>
#include <vector>
using std::string;
using std::vector;
class Header
{
    string nombre_archivo;
    vector<Campo*> campos;
    int list_offset;
    int datos_offset;
public:
    Header(string nombre, vector<Campo*> campos);
    Header(string direccion); // leer archivo
    string getNombre_archivo() const;
    void setNombre_archivo(const string &value);
    vector<Campo*> getCampos() const;
    void setCampos(const vector<Campo*> &value);
    int getList_offset() const;
    void setList_offset(int value);
    int getDatos_offset() const;
    void setDatos_offset(int value);
};

#endif // HEADER_H
