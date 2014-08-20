#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialognuevo.h"
#include "header.h"

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
    Header *header = new Header("personas.dat");
}
