#ifndef DIALOGVER_H
#define DIALOGVER_H

#include <QDialog>
#include <QMap>
#include "header.h"
namespace Ui {
class DialogVer;
}

class DialogVer : public QDialog
{
    Q_OBJECT

public:
    explicit DialogVer(QString path, QWidget *parent = 0);
    QMap<QString,QString> index;
    Header *header;
    ~DialogVer();

private slots:
    void on_pushButton_clicked();

    void on_le_agregar_clicked();

private:
    QString path;
    QList<int> rrn_tabla;
    Ui::DialogVer *ui;
    void llenarTabla();
    bool borrarRegistro(QString llave);
    void leerIndex();
    void reescribirIndice();
};

#endif // DIALOGVER_H
