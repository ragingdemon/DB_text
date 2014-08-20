#include "dialognuevo.h"
#include "ui_dialognuevo.h"

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

void dialogNuevo::on_pushButton_2_clicked()
{

}
