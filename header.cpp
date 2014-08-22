#include "header.h"
#include <QFile>
#include <QTextStream>
#include <fstream>
#include <iostream>
#include <string>

using std::fstream;
using std::string;
using std::vector;
using std::cout;

Header::Header(QString nombre, vector<Campo*> campos)
    :nombre_archivo(nombre),campos(campos)
{
    nombre_archivo.append(".dat");
}

Header::Header(QString direccion)
{
    fstream archivo;
    archivo.open(direccion.toStdString().c_str());
    if (archivo.is_open()) {
        string str;
        while (getline(archivo,str)) {
            if(str.find("nombre de archivo") != string::npos){
                nombre_archivo = QString::fromStdString(str.substr(18));
            }else if(str.find("numero de campos") != string::npos){
                int num_campos = std::stoi(str.substr(17));
                getline(archivo,str);//se salta la linea: campo,nombre,tipo,long,llave
                for (int var = 0; var < num_campos; ++var) {
                    getline(archivo,str);
                    try {
                        campos.push_back(new Campo(str));
                    } catch (...) {
                        cout<<"exception campo"<<'\n';
                    }
                }
            }else if(str.find("longitud de registro") != string::npos){
                list_offset = archivo.tellg() + 10;

            }else if(str.find("availlist") != string::npos){
                datos_offset = archivo.tellg();
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
    QFile archivo(nombre_archivo);
    if (!archivo.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&archivo);
    out<<"nombre de archivo,"<<nombre_archivo<<'\n';
    out<<"numero de campos,"<<campos.size()<<'\n';
    out<<"campo,nombre,tipo,long,llave"<<'\n';
    for (unsigned i = 0; i < campos.size(); ++i) {
        out<<QString::fromStdString(campos.at(i)->toString())<<'\n';
    }
    out<<"longitud de registro,"<<getLongitud_registro()<<'\n';
    out<<"availlist,-1  "<<'\n';
    archivo.close();
    return true;
}
