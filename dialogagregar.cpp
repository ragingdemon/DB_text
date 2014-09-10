#include "dialogagregar.h"
#include "ui_dialogagregar.h"
#include <QTableWidget>
#include <QDebug>
#include <vector>
#include <QFile>
#include <QTextStream>
using std::vector;

DialogAgregar::DialogAgregar(QString path, DialogVer *parent) :
    QDialog(parent),
    ui(new Ui::DialogAgregar)
{
    ui->setupUi(this);
    this->parent = parent;
    this->path = path;
    header = parent->header;
    //identificar la columna llave
    campoLLave = header->campoLLave();
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
        QLineEdit *line = crearLine(campos.at(i));
        table->setCellWidget(0,i,line);
        lines.append(line);
    }
}

DialogAgregar::~DialogAgregar()
{
    delete ui;
    foreach (QLineEdit* line, lines) {
        if(line)
            delete line;
    }
}

void DialogAgregar::on_buttonBox_accepted()
{
    //crear registro de la tabla
    QString registro;
    vector<Campo*> campos = header->getCampos();
    QTableWidget* table = ui->tableWidget;
    for (int i = 0; i < table->columnCount(); ++i) {
            QString str = lines.at(i)->text();
            int longitud = campos.at(i)->getLongitud();

            while (str.size() < longitud) {
                str.append(' ');
            }
            registro.append(str);
            qDebug()<<registro;
    }

    QString llave = lines.at(campoLLave)->text();
    header->insertar_lineal(llave,registro);
}

void DialogAgregar::on_buttonBox_rejected()
{
    this->close();
}

QLineEdit* DialogAgregar::crearLine(Campo* campo)
{
    QString tipo = campo->getTipo();
    int longitud = campo->getLongitud();
    QLineEdit *newLine = new QLineEdit;
    QString mask;
    if (tipo == "char") {
        mask.fill('a',longitud);
        newLine->setInputMask(mask);
    } else if (tipo == "int") {
        mask.fill('0',longitud);
        newLine->setInputMask(mask);
    }
    return newLine;
}
