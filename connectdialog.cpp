#include "connectdialog.h"
#include "ui_connectdialog.h"
#include <QIntValidator>
#include <QMessageBox>
ConnectDialog::ConnectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectDialog)
{
    ui->setupUi(this);
    QString num = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    reg = QRegExp("^" + num +
                  "\\." + num +
                  "\\." + num +
                  "\\." + num + "$");
    ui->lineEdit->setValidator(new QRegExpValidator(reg,this));

}

ConnectDialog::~ConnectDialog()
{
    delete ui;
}

int ConnectDialog::portnumber()
{
    return ui->lineEdit_2->text().toInt();
}

QString ConnectDialog::IP()
{
    return ui->lineEdit->text();
}

void ConnectDialog::accept()
{
    QString ip=ui->lineEdit->text();
    if (ip.indexOf(reg) == -1) {
        QMessageBox::warning(this,"error","你输入的ip地址有误，请重新输入");
        return;
    }
    this->close();
    emit accepted();

}

