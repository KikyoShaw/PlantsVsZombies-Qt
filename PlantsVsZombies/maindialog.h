#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include <QMouseEvent>

#include "zscene.h"

namespace Ui {
class mainDialog;
}

class mainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mainDialog(QWidget *parent = 0);
    zScene* scene;
    ~mainDialog();
protected:

private:
    Ui::mainDialog *ui;
public slots:
    void startLawn();
    void startDark();
    void back();
};

#endif // MAINDIALOG_H
