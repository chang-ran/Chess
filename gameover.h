#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QDialog>

namespace Ui {
class Gameover;
}

class Gameover : public QDialog
{
    Q_OBJECT

public:
    explicit Gameover(QWidget *parent = 0);
    ~Gameover();
    void setlabel(QString);

private:
    Ui::Gameover *ui;
};

#endif // GAMEOVER_H
