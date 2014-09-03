#include "dialogver.h"
#include "ui_dialogver.h"
#include "campo.h"
#include "dialogagregar.h"
#include <QFile>
#include <QTextStream>
#include <QTableWidget>
#include <QInputDialog>
#include <QDebug>
using std::vector;

DialogVer::DialogVer(QString path, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogVer)
{
    ui->setupUi(this);
    this->path = path;
    header = new Header(path);
    llenarTabla();
    leerIndex();
}

DialogVer::~DialogVer()
{
    reescribirIndice();
    if(header)
        delete header;
    delete ui;
}

void DialogVer::llenarTabla()
{
    QTableWidget* table = ui->tableWidget;
    while(table->rowCount() > 0)
        table->removeRow(0);
    vector<Campo*> campos = header->getCampos();
    QStringList encabezados;
    for (unsigned int i = 0; i < campos.size(); ++i) {
        QString str((campos.at(i))->getNombre());
        encabezados.append(str);
    }
    table->setColumnCount(campos.size());
    table->setHorizontalHeaderLabels(encabezados);
    //leer registros del archivo y agregarlos a la tabla
    QFile archivo(path);
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&archivo);
    in.seek(header->getDatos_offset());
    int longitud_registro = header->getLongitud_registro();
    int fila = 0;
    //int rrn = 0;
    while (!in.atEnd()) {
        QString registro = in.read(longitud_registro);
        int offset = 0;
        if (registro.at(0) != '*') {
            //rrn_tabla.append(rrn);
            table->insertRow(fila);
            for (unsigned int i = 0; i < campos.size(); ++i) {
                int incremento = campos.at(i)->getLongitud();
                QString substring = registro.mid(offset,incremento);
                table->setItem(fila,i,new QTableWidgetItem(substring.trimmed()));
                offset += incremento;
            }
            fila++;
        }else{
            offset += longitud_registro;
        }
        //rrn++;
    }
    if (archivo.isOpen()) {
        archivo.close();
    }
}

bool DialogVer::borrarRegistro(QString llave)
{
    int longitud_registro = header->getLongitud_registro();
    QFile archivo(path);
    if (!archivo.open(QIODevice::ReadWrite | QIODevice::Text))
        return false;
    QTextStream in_out(&archivo);
    //leer cabeza del availlist
    in_out.seek(header->getList_offset());
    QString availlist = in_out.readLine();
    int offset = index.value(llave,"").toInt();
    if(!offset){
        qDebug()<<"no se pudo convertir el offset a int";
        return false;
    }
    int rrn = (offset - header->getDatos_offset()) / header->getLongitud_registro();
    qDebug()<<"cabeza de availlist: "<<availlist;
    qDebug()<<"registro a eliminar: "<<rrn;
    //reescribir cabeza del availlist
    in_out.seek(header->getList_offset());
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
    index.remove(llave);
    llenarTabla();
    return true;
}

void DialogVer::leerIndex()
{
    QFile archivo(header->getNombre_archivo() + ".libx");
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&archivo);
    while (!in.atEnd()) {
        QString registro;
        in>>registro;
        QStringList split = registro.split(',');
        if(split.size() > 1)
            index.insert(split.at(0).trimmed(),split.at(1).trimmed());
    }
    archivo.close();
}

void DialogVer::reescribirIndice()
{
    QFile archivo(header->getNombre_archivo() + ".libx");
    if (!archivo.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&archivo);
    QMapIterator<QString, QString> i(index);
    while (i.hasNext()) {
        i.next();
        out << i.key() << "," << i.value() << endl;
    }
    archivo.close();
}

void DialogVer::on_pushButton_clicked()
{
    QTableWidget* table = ui->tableWidget;
    QModelIndexList indexList = table->selectionModel()->selectedIndexes();
    int campo_llave = header->campoLLave();
    if(indexList.size() > 1){
        QModelIndex indice = indexList.at(0);
        QString llave = table->item(indice.row(),campo_llave)->text().trimmed();
        if (index.size() > 0) {
            borrarRegistro(llave);
        }
    }
}


void DialogVer::on_le_agregar_clicked()
{
    DialogAgregar dialog(path,this);
    dialog.exec();
    llenarTabla();
}
