#include "dialogver.h"
#include "ui_dialogver.h"
#include "campo.h"
#include <QFile>
#include <QTextStream>
#include <QTableWidget>
#include <QDebug>
#include <vector>
using std::vector;

DialogVer::DialogVer(QString path, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogVer)
{
    ui->setupUi(this);
    this->path = path;
    header = new Header(path);
    llenarTabla(path);
}

DialogVer::~DialogVer()
{
    if(header)
        delete header;
    delete ui;
}

void DialogVer::llenarTabla(QString path)
{
    QTableWidget* table = ui->tableWidget;
    vector<Campo*> campos = header->getCampos();
    QStringList encabezados;
    for (unsigned int i = 0; i < campos.size(); ++i) {
        QString str((campos.at(i))->getNombre().c_str());
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
    int rrn = 0;
    while (!in.atEnd()) {
        QString registro = in.read(longitud_registro);
        rrn++;
        int offset = 0;
        if (registro.at(0) != '*') {
            rrn_tabla.append(rrn);
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

    }
    if (archivo.isOpen()) {
        archivo.close();
    }
}

bool DialogVer::borrarRegistro(int fila)
{
    QFile archivo(path);
    if (!archivo.open(QIODevice::ReadWrite | QIODevice::Text))
        return false;
    QTextStream out(&archivo);
    //leer cabeza del availlist
    out.seek(header->getList_offset());
    int availlist = out.readLine().trimmed().toInt();
    qDebug()<<"cabeza de availlist: "<<availlist;
    qDebug()<<"registro a eliminar: "<<rrn_tabla.at(fila);
    //reescribir cabeza del availlist
    out.seek(header->getList_offset());
    QString str;
    out<<"";

    return true;
}

void DialogVer::on_pushButton_clicked()
{
    QTableWidget* table = ui->tableWidget;
    QModelIndexList indexList = table->selectionModel()->selectedIndexes();
    int fila;
    foreach (QModelIndex index, indexList) {
        fila = index.row();
        qDebug()<<"row: "<<fila;
        borrarRegistro(fila);
    }
}
