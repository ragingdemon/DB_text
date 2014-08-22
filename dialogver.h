#ifndef DIALOGVER_H
#define DIALOGVER_H

#include <QDialog>
#include "header.h"
namespace Ui {
class DialogVer;
}

class DialogVer : public QDialog
{
    Q_OBJECT

public:
    explicit DialogVer(QString path, QWidget *parent = 0);
    ~DialogVer();

private slots:
    void on_pushButton_clicked();

    void on_le_agregar_clicked();

private:
    QString path;
    Header *header;
    QList<int> rrn_tabla;
    Ui::DialogVer *ui;
    void llenarTabla(QString path);
    bool borrarRegistro(int rrn);
};

#endif // DIALOGVER_H
