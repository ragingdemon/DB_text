#include "header.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>


Header::Header(QString nombre, vector<Campo*> campos)
    :nombre_archivo(nombre),campos(campos)
{

}

Header::Header(QString direccion)
{
    QFile archivo(direccion);
        if (archivo.open(QIODevice::ReadOnly | QIODevice::Text)){
            QTextStream in(&archivo);
            while (!in.atEnd()) {
                QString str = in.readLine();
                qDebug()<<str;
                qDebug()<<"offset: "<<in.pos();
                if (str.contains("nombre de archivo")) {
                    nombre_archivo = str.mid(18);
                }else if (str.contains("numero de campos")) {
                    int num_campos = str.mid(17).toInt();
                    str = in.readLine();
                    qDebug()<<str;
                    qDebug()<<"offset: "<<in.pos();
                    for (int i = 0; i < num_campos; ++i) {
                        str = in.readLine();
                        try {
                            campos.push_back(new Campo(str));
                        } catch (...) {
                            qDebug()<<"error";
                        }
                    }
                }else if (str.contains("longitud de registro")) {
                    list_offset = in.pos() + 10;
                } else if (str.contains("availlist")) {
                    datos_offset = in.pos();
                    break;
                }
            }
        }
        archivo.close();    
}

vector<Campo*> Header::getCampos() const
{
    return campos;
}

void Header::setCampos(const vector<Campo*> &value)
{
    campos = value;
}

QString Header::getNombre_archivo() const
{
    return nombre_archivo;
}

void Header::setNombre_archivo(const QString &value)
{
    nombre_archivo = value;
}

int Header::getList_offset() const
{
    return list_offset;
}

void Header::setList_offset(int value)
{
    list_offset = value;
}

int Header::getDatos_offset() const
{
    return datos_offset;
}

void Header::setDatos_offset(int value)
{
    datos_offset = value;
}

int Header::getLongitud_registro()
{
    longitud_registro = 0;
    for (unsigned int i = 0; i < campos.size(); ++i) {
        longitud_registro += campos.at(i)->getLongitud();
    }
    return longitud_registro;
}

bool Header::crearArchivo()
{
    QFile archivo(nombre_archivo + ".dat");
    if (!archivo.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&archivo);
    out<<"nombre de archivo,"<<nombre_archivo<<'\n';
    out<<"numero de campos,"<<campos.size()<<'\n';
    out<<"campo,nombre,tipo,long,llave"<<'\n';
    for (unsigned i = 0; i < campos.size(); ++i) {
        out<<campos.at(i)->toString()<<'\n';
    }
    out<<"longitud de registro,"<<getLongitud_registro()<<'\n';
    out<<"availlist,-1   "<<'\n';
    archivo.close();
    archivo.setFileName(nombre_archivo + ".libx");
    if (!archivo.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    archivo.close();
    return true;
}

int Header::campoLLave()
{
    for (unsigned i = 0; i < campos.size(); ++i) {
        Campo *campo = campos.at(i);
        if(campo->getLlave())
            return i;
    }
    return -1;
}
