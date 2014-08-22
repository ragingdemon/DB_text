#include "dialogagregar.h"
#include "ui_dialogagregar.h"
#include <vector>
using std::vector;

DialogAgregar::DialogAgregar(QString path, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAgregar)
{
    ui->setupUi(this);
    this->path = path;
    header = new Header(path);
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
    }
}

DialogAgregar::~DialogAgregar()
{
    delete ui;
}

void DialogAgregar::on_buttonBox_accepted()
{

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
