#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialognuevo.h"
#include "dialogver.h"
#include "dialogcruce.h"
#include "header.h"
#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include "arbolb.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    dialogNuevo dialog(this);
    dialog.exec();
}

void MainWindow::on_pushButton_2_clicked()
{
    try {
        QString path(QFileDialog::getOpenFileName(this,tr("Abrir Archivo"), "./", tr("DAT Files (*.dat)")));
        QFile archivo(path);
        if (!archivo.exists()){
            return;
        }
        if (archivo.isOpen()) {
            archivo.close();
        }
        DialogVer dialog(path,this);
        dialog.exec();
    } catch (...) {
    }
}

void MainWindow::on_pb_cruce_clicked()
{
    DialogCruce dialog(this);
    dialog.exec();
}
