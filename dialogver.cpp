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
}

DialogVer::~DialogVer()
{
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
    while (!in.atEnd()) {
        QString registro = in.read(longitud_registro);
        int offset = 0;
        if (registro.at(0) != '*') {
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


void DialogVer::on_pushButton_clicked()
{
    QTableWidget* table = ui->tableWidget;
    QModelIndexList indexList = table->selectionModel()->selectedIndexes();
    int campo_llave = header->campoLLave();
    if(indexList.size() > 1){
        QModelIndex indice = indexList.at(0);
        QString llave = table->item(indice.row(),campo_llave)->text().trimmed();
        if (header->indice_linea->index.size() > 0) {
            header->eliminar_lineal(llave);
            llenarTabla();
        }
    }
}


void DialogVer::on_le_agregar_clicked()
{
    DialogAgregar dialog(path,this);
    dialog.exec();
    llenarTabla();
}
