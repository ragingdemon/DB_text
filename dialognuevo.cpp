#include "dialognuevo.h"
#include "ui_dialognuevo.h"
#include "header.h"
#include <QDebug>


dialogNuevo::dialogNuevo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogNuevo)
{
    ui->setupUi(this);
}

dialogNuevo::~dialogNuevo()
{
    for (unsigned i = 0; i < campos.size(); ++i) {
        Campo* toDelete = campos.at(i);
        if(toDelete)
            delete toDelete;
    }
    delete ui;
}

void dialogNuevo::on_pb_campo_clicked()
{
    int campo = campos.size() + 1;
    QString nombre = ui->le_campo->text();
    QString tipo = ui->comboBox->currentText();
    int longitud = ui->spinBox->value();
    bool llave = ui->checkBox->isChecked();
    //validar que no exista mas de una llave
    if(llave)
        if(existe_llave()){
            qDebug()<<"Solo se permite una llave";
            return;
        }
    try {
        campos.push_back(new Campo(campo,nombre,tipo,longitud,llave));
    } catch (...) {
        qDebug()<<"Error al crear campo";
        return;
    }
    for (unsigned i = 0; i < campos.size(); ++i) {
        qDebug()<<campos.at(i);
    }
}

void dialogNuevo::on_pb_archivo_clicked()
{
    if (campos.size() == 0) {
        qDebug()<<"necesita campos para crear tablas"<<'\n';
        return;
    }
    QString nombre = ui->le_archivo->text().trimmed();
    if (nombre.isEmpty()) {
        qDebug()<<"necesita un nombre para el archivo"<<'\n';
        return;
    }
    Header *header = new Header(nombre,campos);
    if (!header->crearArchivo()) {
        qDebug()<<"Error, no se creó el archivo";
        return;
    }    
    this->close();
}

bool dialogNuevo::existe_llave() const
{
    for (unsigned i = 0; i < campos.size(); ++i) {
        Campo* campo = campos.at(i);
        if(campo->getLlave())
            return true;
    }
    return false;
}
