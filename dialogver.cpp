#include "dialogver.h"
#include "ui_dialogver.h"

DialogVer::DialogVer(QString path, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogVer)
{
    ui->setupUi(this);
    header = new Header(path.toStdString());
}

DialogVer::~DialogVer()
{
    if(header)
        delete header;
    delete ui;
}
