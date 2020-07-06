#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "createdialog.h"
#include "connectdialog.h"
#include <QtNetwork>
#include "chessboard.h"
#include "gameover.h"
#include <QTimer>
#include <QLCDNumber>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ConnectDialog * connectdialog = new ConnectDialog;
    CreateDialog * createdialog = new CreateDialog;
    QTcpServer * server;
    QTcpSocket * socket;
    ChessBoard * chessboard =new ChessBoard(this);
    Gameover * gameover;
    QTimer * timer = new QTimer(this);
    int second;
    QLCDNumber * lcd= new QLCDNumber(this);


public slots:
    void connectaction();
    void createaction();
    void createserver();
    void createclient();
    void acceptconnection();
    void setdisconnect();
    void getload();
    void sendmessage();
    void receivemessage();
    void giveup();
    void record();
    void save();
    void restart();
signals:
    void num(int);
};

#endif // MAINWINDOW_H
