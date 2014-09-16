#ifndef LLAVE_H
#define LLAVE_H

#include <QString>

class Llave
{
    QString llave;
    QString rrn;
    int llave_size;
    int rrn_size;
public:
    Llave(QString llave,int llave_size);
    Llave(QString llave, QString rrn,int llave_size, int rrn_size);
    Llave(QString toSplit,int llave_size, int rrn_size);
    QString getLlave() const;
    void setLlave(const QString &value);
    QString getRrn() const;
    void setRrn(const QString &value);
    int rrntoInt()const;
    bool operator ==(Llave &l)const;
    bool operator ==(Llave *l)const;
    bool operator <(Llave &l)const;
    bool operator <(Llave *l)const;
    bool operator >(Llave &l)const;
    bool operator >(Llave *l)const;
};

#endif // LLAVE_H
