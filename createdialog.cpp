#include "createdialog.h"
#include "ui_createdialog.h"
#include <QtNetwork>
#include <QDebug>
CreateDialog::CreateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateDialog)
{
    ui->setupUi(this);
    ui->label_3->setText("183.172.210.72");
    QObject::connect(ui->pushButton,SIGNAL(clicked(bool)),this, SLOT(waiting()));
    QObject::connect(waitingdialog,SIGNAL(setcancel()),this,SLOT(setcancel()));
}

CreateDialog::~CreateDialog()
{
    delete ui;
}

int CreateDialog::portnumber()
{
    return ui->lineEdit->text().toInt();
}

void CreateDialog::waiting()
{
    waitingdialog->show();

}

void CreateDialog::setcancel()
{
    emit setdisconnect();
}
