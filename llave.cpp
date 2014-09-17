#include "llave.h"

Llave::Llave(QString llave, int llave_size):
    llave(llave),llave_size(llave_size)
{
    while (llave.size() < llave_size) {
        llave.append(' ');
    }
}

Llave::Llave(QString llave, QString rrn, int llave_size, int rrn_size):
    llave(llave), rrn(rrn), llave_size(llave_size), rrn_size(rrn_size)
{
    while (llave.size() < llave_size) {
        llave.append(' ');
    }
    while (rrn.size() < rrn_size) {
        rrn.append(' ');
    }
}

Llave::Llave(QString toSplit, int llave_size, int rrn_size):
    llave_size(llave_size), rrn_size(rrn_size)
{
    this->llave = toSplit.mid(0,llave_size);
    this->rrn = toSplit.mid(llave_size,rrn_size);
    while (llave.size() < llave_size) {
        llave.append(' ');
    }
    while (rrn.size() < rrn_size) {
        rrn.append(' ');
    }
}

QString Llave::getRrn() const
{
    return rrn;
}

void Llave::setRrn(const QString &value)
{
    rrn = value;
}

QString Llave::getLlave() const
{
    return llave;
}

void Llave::setLlave(const QString &value)
{
    llave = value;
}

int Llave::rrntoInt() const
{
    return rrn.toInt();
}

bool Llave::operator ==(Llave &l) const
{
    int compare = QString::compare(llave,l.llave,Qt::CaseInsensitive);
    if(compare == 0)
        return true;
    return false;
}

bool Llave::operator ==(Llave *l) const
{
    if (l == nullptr) {
        return false;
    }
    int compare = QString::compare(llave,l->llave,Qt::CaseInsensitive);
    if(compare == 0)
        return true;
    return false;
}

bool Llave::operator <(Llave &l) const
{
    int compare = QString::compare(llave,l.llave,Qt::CaseInsensitive);
    if(compare < 0)
        return true;
    return false;
}

bool Llave::operator <(Llave *l) const
{
    if (l == nullptr) {
        return false;
    }
    int compare = QString::compare(llave,l->llave,Qt::CaseInsensitive);
    if(compare < 0)
        return true;
    return false;
}

bool Llave::operator >(Llave &l) const
{
    int compare = QString::compare(llave,l.llave,Qt::CaseInsensitive);
    if(compare > 0)
        return true;
    return false;
}

bool Llave::operator >(Llave *l) const
{
    if (l == nullptr) {
        return false;
    }
    int compare = QString::compare(llave,l->llave,Qt::CaseInsensitive);
    if(compare > 0)
        return true;
    return false;
}
