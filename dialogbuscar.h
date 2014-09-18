#ifndef DIALOGBUSCAR_H
#define DIALOGBUSCAR_H

#include <QDialog>
#include <QLineEdit>
#include "dialogver.h"
#include "header.h"
#include "campo.h"

namespace Ui {
class DialogBuscar;
}

class DialogBuscar : public QDialog
{
    Q_OBJECT

public:
    explicit DialogBuscar(QStringList registro, DialogVer *parent = 0);
    ~DialogBuscar();

private:
    Header *header;
    DialogVer *parent;
    Ui::DialogBuscar *ui;
};

#endif // DIALOGBUSCAR_H
