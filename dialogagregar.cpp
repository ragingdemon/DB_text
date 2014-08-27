#include "dialogagregar.h"
#include "ui_dialogagregar.h"
#include <QTableWidget>
#include <QDebug>
#include <vector>
#include <QFile>
#include <QTextStream>
using std::vector;

DialogAgregar::DialogAgregar(QString path, QMap<QString,QString> &index, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAgregar)
{
    ui->setupUi(this);
    this->path = path;
    header = new Header(path);
    this->index = index;
    //identificar la columna llave
    campoLLave = header->campoLLave();
    //llenar tabla con line edits para ingresar datos
    QTableWidget* table = ui->tableWidget;
    vector<Campo*> campos = header->getCampos();
    QStringList encabezados;
    for (unsigned int i = 0; i < campos.size(); ++i) {
        QString str((campos.at(i))->getNombre().c_str());
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
    //leer cabeza del availlist
    //int longitud_registro = header->getLongitud_registro();
    QFile archivo(path);
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&archivo);
    in.seek(header->getList_offset());
    int availlist = in.readLine().toInt();
    archivo.close();
    if (availlist == -1) {
        append_registro(registro);
    }else{
        rewrite_registro(registro,availlist);
    }
}

void DialogAgregar::on_buttonBox_rejected()
{
    this->close();
}

QLineEdit* DialogAgregar::crearLine(Campo* campo)
{
    QString tipo = QString::fromStdString(campo->getTipo());
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

bool DialogAgregar::append_registro(QString registro)
{
    //verificar si la llave ya existe en el indice
    QString llave = lines.at(campoLLave)->text();
    if(index.contains(llave)){
        qDebug()<<"la llave ya existe";
        return false;
    }
    //agregar el registro a la base de datos
    QFile archivo(path);
    if (!archivo.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
        return false;
    QTextStream out(&archivo);
    int offset = out.pos();
    out<<registro;
    archivo.close();
    //agregar al indice
    index.insert(llave,QString::number(offset));
    return true;
}

bool DialogAgregar::rewrite_registro(QString registro, int &availlist)
{
    //verificar si la llave ya existe en el indice
    QString llave = lines.at(campoLLave)->text();
    if(index.contains(llave)){
        qDebug()<<"la llave ya existe";
        return false;
    }
    //
    int offset = header->getDatos_offset() + (availlist * header->getLongitud_registro());
    QFile archivo(path);
    if (!archivo.open(QIODevice::ReadWrite| QIODevice::Text))
        return false;
    QTextStream out(&archivo);
    return true;
}




