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
    archivo.setFileName(direccion);
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
                    longitud_registro = str.mid(21).toInt();
                    qDebug()<<"el erorr era: "<<QString::number(longitud_registro);
                    list_offset = in.pos() + 10;
                } else if (str.contains("availlist")) {
                    datos_offset = in.pos();
                    break;
                }
            }
        }
        archivo.close();
        indice_linea = new IndiceL(direccion.mid(0,direccion.size()-4));
        indice_linea->leer_indice();
}

Header::~Header()
{
    if(indice_linea)
        delete indice_linea;
    for (unsigned i = 0; i < campos.size(); ++i) {
        delete campos.at(i);
    }
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
    return longitud_registro;
}

bool Header::crearArchivo()
{
    archivo.setFileName(nombre_archivo + ".dat");
    if (!archivo.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&archivo);
    out<<"nombre de archivo,"<<nombre_archivo<<'\n';
    out<<"numero de campos,"<<campos.size()<<'\n';
    out<<"campo,nombre,tipo,long,llave"<<'\n';
    for (unsigned i = 0; i < campos.size(); ++i) {
        out<<campos.at(i)->toString()<<'\n';
    }
    int l = 0;
    for (unsigned int i = 0; i < campos.size(); ++i) {
        l += campos.at(i)->getLongitud();
    }
    out<<"longitud de registro,"<<l<<'\n';
    out<<"availlist,-1   "<<'\n';
    archivo.close();    
    //crear indice lineal
    archivo.setFileName(nombre_archivo + ".libx");
    if (!archivo.open(QIODevice::ReadWrite | QIODevice::Text))
        return false;
    archivo.close();

    indice_linea = new IndiceL(nombre_archivo);
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

int Header::getAvaillist_head()
{
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"No se puede abrir el archivo";
        return -1;
    }
    QTextStream in(&archivo);
    in.seek(list_offset);
    int availlist = in.readLine().toInt();
    archivo.close();
    return availlist;
}

void Header::setAvailList_head(int availlist)
{
    int offset = datos_offset + (availlist * longitud_registro);
    if (!archivo.open(QIODevice::ReadWrite| QIODevice::Text))
        return;
    QTextStream in_out(&archivo);
    //obtener siguiente elemento del availlist
    in_out.seek(offset+1);
    QString rrn = in_out.read(5);
    //reescribir cabeza del availlist
    in_out.seek(list_offset);
    in_out<<rrn;
    archivo.close();
}

bool Header::insertar_lineal(QString llave, QString registro)
{
    if(indice_linea->index.contains(llave)){
        qDebug()<<"la llave ya existe";
        return false;
    }
    qDebug()<<archivo.fileName();
    qDebug()<<indice_linea->archivo.fileName();
    int availlist = getAvaillist_head();    
    if (availlist == -1) {
        if (!archivo.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
            return false;
        QTextStream out(&archivo);
        int offset = out.pos();
        out<<registro;
        archivo.close();
        //agregar al indice
        indice_linea->index.insert(llave,QString::number(offset));
    }else{
        int offset = datos_offset + (availlist * longitud_registro);
        setAvailList_head(availlist);
        if (!archivo.open(QIODevice::ReadWrite| QIODevice::Text))
            return false;
        QTextStream in_out(&archivo);
        //reescribir regsitro
        in_out.seek(offset);
        in_out<<registro;
        //agregar al indice
        indice_linea->index.insert(llave,QString::number(offset));
        archivo.close();
    }    
    return true;
}

bool Header::eliminar_lineal(QString llave)
{
    if (!archivo.open(QIODevice::ReadWrite | QIODevice::Text))
        return false;
    QTextStream in_out(&archivo);
    //leer cabeza del availlist
    in_out.seek(getList_offset());
    QString availlist = in_out.readLine();
    int offset = indice_linea->index.value(llave,"").toInt();
    if(!offset){
        qDebug()<<"no se pudo convertir el offset a int";
        return false;
    }
    int rrn = (offset - getDatos_offset()) / getLongitud_registro();
    qDebug()<<"cabeza de availlist: "<<availlist;
    qDebug()<<"registro a eliminar: "<<rrn;
    //reescribir cabeza del availlist
    in_out.seek(getList_offset());
    QString str = QString::number(rrn);
    while (str.size() < 5) {
        str.append(' ');
    }
    in_out<<str;
    //marcar registro como borrado
    in_out.seek(offset);
    str = "*" + availlist;
    qDebug()<<"offset del registro a eliminar: "<<in_out.pos();
    in_out<<str;
    archivo.close();
    //eliminar registro del indice
    indice_linea->index.remove(llave);
    return true;
}
