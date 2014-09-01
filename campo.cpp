#include "campo.h"
#include <stdexcept>
#include <QStringList>
using std::invalid_argument;


Campo::Campo(int campo, QString nombre, QString tipo, int longitud, bool llave)
    : campo(campo),nombre(nombre),tipo(tipo),longitud(longitud),llave(llave)
{

}

Campo::Campo(QString datos)
{
    QStringList tokens = datos.split(',');
    if(tokens.size() < 5)
        throw invalid_argument("datos insuficientes");
    campo = tokens.at(0).toInt();
    nombre = tokens.at(1);
    tipo = tokens.at(2);
    longitud = tokens.at(3).toInt();
    llave = tokens.at(4).toInt();
}

int Campo::getCampo() const
{
    return campo;
}

void Campo::setCampo(int value)
{
    campo = value;
}

QString Campo::getNombre() const
{
    return nombre;
}

void Campo::setNombre(const QString &value)
{
    nombre = value;
}

QString Campo::getTipo() const
{
    return tipo;
}

void Campo::setTipo(const QString &value)
{
    tipo = value;
}

int Campo::getLongitud() const
{
    return longitud;
}

void Campo::setLongitud(int value)
{
    longitud = value;
}

bool Campo::getLlave() const
{
    return llave;
}

void Campo::setLlave(bool value)
{
    llave = value;
}

QString Campo::toString() const
{
    QString ss = QString::number(campo) + ',' + nombre + ',' + tipo + ',' + QString::number(longitud )+ ',' + QString::number(llave);
    return ss;
}
