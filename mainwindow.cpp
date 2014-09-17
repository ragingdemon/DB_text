#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialognuevo.h"
#include "dialogver.h"
#include "header.h"
#include <QFileDialog>
#include <QFile>
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
        QString path(QFileDialog::getOpenFileName(this,tr("Open Image"), "./", tr("DAT Files (*.dat)")));
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

void MainWindow::on_pushButton_4_clicked()
{
    ArbolB *arbol = new ArbolB("yreuiwqyr",10,5,6);
    for (int i = 0; i < 10; ++i) {
        QString llave = QString::number(i);
        QString rrn = QString::number(i);
        Llave *l = new Llave(llave,rrn,5,5);
        arbol->insertar(l);
    }
}
