#include "dialogver.h"
#include "ui_dialogver.h"
#include "campo.h"
#include <QFile>
#include <QTextStream>
#include <QTableWidget>
#include <vector>
using std::vector;

DialogVer::DialogVer(QString path, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogVer)
{
    ui->setupUi(this);
    header = new Header(path.toStdString());
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
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    in.seek(header->getDatos_offset());
    int longitud_registro = header->getLongitud_registro();
    int fila = 0;
    while (!in.atEnd()) {
        QString registro = in.read(longitud_registro);
        int offset = 0;
        table->insertRow(fila);
        for (unsigned int i = 0; i < campos.size(); ++i) {
            int incremento = campos.at(i)->getLongitud();
            QString substring = registro.mid(offset,incremento);
            table->setItem(fila,i,new QTableWidgetItem(substring.trimmed()));
            offset += incremento;
        }
        fila++;
    }
    if (file.isOpen()) {
        file.close();
    }
}
