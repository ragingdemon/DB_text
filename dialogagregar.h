#ifndef DIALOGAGREGAR_H
#define DIALOGAGREGAR_H

#include <QDialog>
#include <QLineEdit>
#include "dialogver.h"
#include "header.h"
#include "campo.h"
namespace Ui {
class DialogAgregar;
}

class DialogAgregar : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAgregar(QString path, DialogVer *parent = 0);
    ~DialogAgregar();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    int campoLLave;
    QString path;
    Header *header;
    DialogVer *parent;
    Ui::DialogAgregar *ui;
    QList<QLineEdit*> lines;
    QLineEdit *crearLine(Campo* campo);
    bool append_registro(QString registro);
    bool rewrite_registro(QString registro, int &availlist);
};

#endif // DIALOGAGREGAR_H
