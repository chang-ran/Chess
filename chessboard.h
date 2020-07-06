#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include <QMouseEvent>
#include "stone.h"
#include "gameover.h"
class ChessBoard : public QWidget
{
    Q_OBJECT
public:
    explicit ChessBoard(QWidget * parent= nullptr);
    void paintEvent(QPaintEvent * event);
    void mousePressEvent(QMouseEvent * event);
    int selected,chosen,turn;
    Stone *stone[33];
    QPixmap images[33];
    Gameover * gameover;
    bool isclient;
    QString str;
    void reset();
signals:
    void over();
signals:
    void sendstr();
};

#endif // CHESSBOARD_H
