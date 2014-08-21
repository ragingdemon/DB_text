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

private:
    Header *header;
    Ui::DialogVer *ui;
};

#endif // DIALOGVER_H
