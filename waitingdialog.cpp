#include "waitingdialog.h"
#include "ui_waitingdialog.h"

WaitingDialog::WaitingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WaitingDialog)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton,SIGNAL(clicked(bool)),this , SLOT(cancel()));
}

WaitingDialog::~WaitingDialog()
{
    delete ui;
}

void WaitingDialog::cancel()
{
    emit setcancel();
    this->close();
}

