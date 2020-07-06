#include "gameover.h"
#include "ui_gameover.h"

Gameover::Gameover(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gameover)
{
    ui->setupUi(this);
}

Gameover::~Gameover()
{
    delete ui;
}

void Gameover::setlabel(QString t)
{
    ui->label_2->setText(t);
}
