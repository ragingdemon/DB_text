#include "dialogcruce.h"
#include "ui_dialogcruce.h"
#include <QFileDialog>
#include <QFile>
#include <QDebug>

DialogCruce::DialogCruce(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCruce)
{
    ui->setupUi(this);
    principal = nullptr;
    secundario = nullptr;
}

DialogCruce::~DialogCruce()
{
    if(principal)
        delete principal;
    if(principal)
        delete principal;
    delete ui;
}

void DialogCruce::on_pb_llenar_tabla_clicked()
{
    unsigned campo_tabla1 = ui->sb_sustitucion->value();
    unsigned campo_tabla2 = ui->sb_sustitucion_2->value();
    if (!principal || !secundario) {
        return;
    }
    QTableWidget* table = ui->tableWidget;
    while(table->rowCount() > 0)
        table->removeRow(0);
    vector<Campo*> campos = principal->getCampos();
    QStringList encabezados;
    for (unsigned int i = 0; i < campos.size(); ++i) {
        QString str((campos.at(i))->getNombre());
        encabezados.append(str);
    }
    table->setColumnCount(campos.size());
    table->setHorizontalHeaderLabels(encabezados);
    //leer registros del archivo y agregarlos a la tabla
    QMapIterator<QString, QString> iterator(principal->indice_linea->index);
    int fila = 0;
    while (iterator.hasNext()) {
        iterator.next();
        table->insertRow(fila);
        QStringList registro_tabla1(principal->getRegistro(iterator.value().toInt()));
        qDebug()<<registro_tabla1;
//        int offset_tabla2 = secundario->indice_linea->index.value(registro_tabla1.);
        QStringList registro_tabla2(secundario->getRegistro(registro_tabla1.at(campo_tabla1)));
        qDebug()<<registro_tabla2;
        for (unsigned columna = 0; columna < campos.size(); ++columna) {
            if (columna == campo_tabla1) {
                table->setItem(fila,columna,new QTableWidgetItem(registro_tabla2.at(campo_tabla2)));
            } else {
                table->setItem(fila,columna,new QTableWidgetItem(registro_tabla1.at(columna)));
            }
        }
        fila++;
    }
}

void DialogCruce::on_pb_tabla1_clicked()
{
    try {
        QString path(QFileDialog::getOpenFileName(this,tr("Abrir Archivo"), "./", tr("DAT Files (*.dat)")));
        QFile archivo(path);
        if (!archivo.exists()){
            return;
        }
        if (archivo.isOpen()) {
            archivo.close();
        }
        if (!path.isNull()) {
            ui->le_archivo1->setText(path);
            principal = new Header(path);
        }
    } catch (...) {
    }
}

void DialogCruce::on_pb_tabla1_2_clicked()
{
    try {
        QString path(QFileDialog::getOpenFileName(this,tr("Abrir Archivo"), "./", tr("DAT Files (*.dat)")));
        QFile archivo(path);
        if (!archivo.exists()){
            return;
        }
        if (archivo.isOpen()) {
            archivo.close();
        }
        if (!path.isNull()) {
            ui->le_archivo2->setText(path);
            secundario = new Header(path);
        }
    } catch (...) {
    }
}
