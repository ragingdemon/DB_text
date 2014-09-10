#include "indicel.h"
#include <QTextStream>
#include <QDebug>
IndiceL::IndiceL()
{

}

IndiceL::IndiceL(QString nombre)
{
    archivo.setFileName(nombre + ".libx");
    archivo.open(QIODevice::ReadWrite | QIODevice::Text);
    archivo.close();
    leer_indice();
}

IndiceL::~IndiceL()
{
    reescribir_indice();
}

bool IndiceL::leer_indice()
{
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    QTextStream in(&archivo);
    while (!in.atEnd()) {
        QString registro;
        in>>registro;
        QStringList split = registro.split(',');
        if(split.size() > 1)
            index.insert(split.at(0).trimmed(),split.at(1).trimmed());
    }
    archivo.close();
    return true;
}

bool IndiceL::reescribir_indice()
{
    if (!archivo.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QTextStream out(&archivo);
    QMapIterator<QString, QString> i(index);
    while (i.hasNext()) {
        i.next();
        out << i.key() << "," << i.value() << '\n';
    }
    archivo.close();
    return true;
}
