#include "dialognuevo.h"
#include "ui_dialognuevo.h"
#include "header.h"
#include <QDebug>
using std::vector;

dialogNuevo::dialogNuevo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogNuevo)
{
    ui->setupUi(this);
}

dialogNuevo::~dialogNuevo()
{
    delete ui;
}

void dialogNuevo::on_pb_campo_clicked()
{
    int campo = campos.size() + 1;
    QString nombre = ui->le_campo->text();
    QString tipo = ui->comboBox->currentText();
    int longitud = ui->spinBox->value();
    bool llave = ui->checkBox->isChecked();
    try {
        campos.push_back(new Campo(campo,nombre.toStdString(),tipo.toStdString(),longitud,llave));
    } catch (...) {
        qDebug()<<"Error al crear campo"<<'\n';
        return;
    }
    for (unsigned i = 0; i < campos.size(); ++i) {
        qDebug()<<campos.at(i)->toString().c_str();
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
