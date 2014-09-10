#ifndef INDICEL_H
#define INDICEL_H

#include <QFile>
#include <QMap>
class IndiceL
{

public:
    QFile archivo;
    QMap<QString,QString> index;
    IndiceL();
    IndiceL(QString nombre);
    ~IndiceL();
    bool leer_indice();
    bool reescribir_indice();
};

#endif // INDICEL_H
