#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include <QRegExp>
namespace Ui {
class ConnectDialog;
}

class ConnectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectDialog(QWidget *parent = 0);
    ~ConnectDialog();
    int portnumber();
    QString IP();
    QRegExp reg;

public slots:
    void accept() ;
private:
    Ui::ConnectDialog *ui;
};

#endif // CONNECTDIALOG_H
