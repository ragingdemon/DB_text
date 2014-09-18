#include "dialogbuscar.h"
#include "ui_dialogbuscar.h"
#include <QTableWidget>

DialogBuscar::DialogBuscar(QStringList registro, DialogVer *parent) :
    QDialog(parent),
    ui(new Ui::DialogBuscar)
{
    ui->setupUi(this);
    this->parent = parent;
    header = parent->header;
    //llenar tabla con line edits para ingresar datos
    QTableWidget* table = ui->tableWidget;
    vector<Campo*> campos = header->getCampos();
    QStringList encabezados;
    for (unsigned int i = 0; i < campos.size(); ++i) {
        QString str((campos.at(i))->getNombre());
        encabezados.append(str);
    }
    table->setColumnCount(campos.size());
    table->setRowCount(1);
    table->setHorizontalHeaderLabels(encabezados);
    for (unsigned i = 0; i < campos.size(); ++i) {
        table->setItem(0,i,new QTableWidgetItem(registro.at(i).trimmed()));
    }
}

DialogBuscar::~DialogBuscar()
{
    delete ui;    
}
