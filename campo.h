#ifndef CAMPO_H
#define CAMPO_H
#include <QString>
class Campo
{
    int campo;
    QString nombre;
    QString tipo;
    int longitud;
    bool llave;
public:
    Campo(int campo,QString nombre,QString tipo,int longitud,bool llave);
    Campo(QString datos);
    int getCampo() const;
    void setCampo(int value);
    QString getNombre() const;
    void setNombre(const QString &value);
    QString getTipo() const;
    void setTipo(const QString &value);
    int getLongitud() const;
    void setLongitud(int value);
    bool getLlave() const;
    void setLlave(bool value);
    QString toString()const;
};

#endif // CAMPO_H
