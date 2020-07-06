#ifndef CREATEDIALOG_H
#define CREATEDIALOG_H

#include <QDialog>
#include <waitingdialog.h>
namespace Ui {
class CreateDialog;
}

class CreateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateDialog(QWidget *parent = 0);
    ~CreateDialog();
    int portnumber();
    WaitingDialog * waitingdialog = new WaitingDialog(this);
    Ui::CreateDialog *ui;
public slots:
    void waiting();
    void setcancel();

signals:
    void setdisconnect();

private:


};

#endif // CREATEDIALOG_H
