#ifndef HEADER_H
#define HEADER_H

#include "campo.h"
#include "indicel.h"
#include <QString>
#include <QFile>
using std::vector;
class Header
{
    QString nombre_archivo;
    vector<Campo*> campos;
    int list_offset;
    int datos_offset;
    int longitud_registro;
    QFile archivo;

public:
    IndiceL *indice_linea;
    Header(QString nombre, vector<Campo*> campos);
    Header(QString direccion); // leer archivo
    ~Header();
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
    int campoLLave();
    int getAvaillist_head();
    void setAvailList_head(int availlist);
    bool insertar_lineal(QString llave, QString registro);
    bool eliminar_lineal(QString llave);
};

#endif // HEADER_H
