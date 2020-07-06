#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QPainter>
#include <QSound>
#include <fstream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(800,700);
    chessboard->setVisible(false);
    second=10;
    ui->actionGive_up->setDisabled(true);
    ui->actionLoad->setDisabled(true);
    ui->actionrestart->setDisabled(true);
    ui->actionSave->setDisabled(true);
    lcd->setVisible(false);
    QObject::connect(ui->actionConnect,SIGNAL(triggered(bool)), this, SLOT(connectaction()));
    QObject::connect(ui->actionCreate,SIGNAL(triggered(bool)), this, SLOT(createaction()));
    QObject::connect(ui->actionLoad,SIGNAL(triggered(bool)),this, SLOT(getload()));
    QObject::connect(ui->actionSave,SIGNAL(triggered(bool)),this,SLOT(save()));
    QObject::connect(createdialog,SIGNAL(accepted()),this, SLOT(createserver()));
    QObject::connect(createdialog,SIGNAL(setdisconnect()),this ,SLOT(setdisconnect()));
    QObject::connect(connectdialog,SIGNAL(accepted()),this, SLOT(createclient()));
    QObject::connect(chessboard,SIGNAL(sendstr()),this,SLOT(sendmessage()));
    QObject::connect(ui->actionGive_up,SIGNAL(triggered(bool)),this, SLOT(giveup()));
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(record()));
    QObject::connect(this ,SIGNAL(num(int)),lcd,SLOT(display(int)));
    QObject::connect(ui->actionrestart,SIGNAL(triggered(bool)),this, SLOT(restart()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectaction()// 设置client
{
    connectdialog->show();
}

void MainWindow::createaction() //设置server
{
    createdialog->show();

}

void MainWindow::createserver() //创建server
{
    qDebug()<<"create server";
    server = new QTcpServer;
    server->listen(QHostAddress::Any, createdialog->portnumber());
    QObject::connect(server,SIGNAL(newConnection()),this, SLOT(acceptconnection()));

}

void MainWindow::createclient()//创建client
{
    qDebug()<<"create client";
    socket = new QTcpSocket;
    socket->connectToHost(connectdialog->IP(),connectdialog->portnumber());
    socket->waitForConnected(50000);
    if (socket->state() == QTcpSocket::ConnectedState){
        ui->actionGive_up->setDisabled(true);
        //ui->actionLoad->setDisabled(true);
       // ui->actionrestart->setDisabled(true);
        ui->actionSave->setDisabled(true);
       // ui->actionLoad->setDisabled(true);
        qDebug()<<1;
    QObject::connect(socket,SIGNAL(readyRead()),this,SLOT(receivemessage()));
    chessboard->setVisible(true);

    if(centralWidget()!=nullptr) delete centralWidget();
    setCentralWidget(chessboard);
    lcd->setGeometry(600,300,100,50);
    lcd->setVisible(true);
    emit num(10);
    chessboard->isclient=true;
    ui->actionLoad->setDisabled(true);}
    else {delete socket;qDebug()<<2;}

}

void MainWindow::acceptconnection()
{
    ui->actionGive_up->setDisabled(false);
    ui->actionLoad->setDisabled(false);
    ui->actionrestart->setDisabled(false);
    ui->actionSave->setDisabled(false);
    qDebug()<<"connected";
    socket= server->nextPendingConnection();
    server->close();
    QObject::connect(socket,SIGNAL(readyRead()),this,SLOT(receivemessage()));
    createdialog->waitingdialog->close();
    chessboard->setVisible(true);
    if(centralWidget()!=nullptr) delete centralWidget();
    setCentralWidget(chessboard);
    lcd->setGeometry(600,300,100,50);
    lcd->setVisible(true);
    emit num(10);
    chessboard->isclient=false;
    timer->start(1000);
}

void MainWindow::setdisconnect()
{
    server->close();
}



void MainWindow::sendmessage()
{
    ui->actionLoad->setDisabled(true);
    second=10;
    emit num(10);
    timer->stop();
    qDebug()<<"send";
    qDebug()<<chessboard->str;
    QByteArray *array=new QByteArray;
    array->clear();
    array->append(chessboard->str);
    //array->append("abcd");
    this->socket->write(array->data());
}

void MainWindow::receivemessage()
{
    ui->actionLoad->setDisabled(true);
    bool isover=false;
    qDebug()<<"receive";
    QString _str;
    _str+=socket->readAll();
    qDebug()<<_str;
    //chessboard->turn=1;
    if (_str=="giveup")
    {
        gameover= new Gameover(this);
        gameover->setlabel("对方投降了！");
        gameover->show();
        isover=true;
        //timer->stop();
    }
    if( _str=="timeout")
    {
        gameover= new Gameover(this);
        gameover->setlabel("对方超时了！");
        gameover->show();
        isover=true;
        //timer->stop();
    }
    emit num(10);
    int c[10]= {10,1,2,3,4,5,6,7,8,9};
    QString d="0123456789";
    for (int i=1; i<65; i=i+2)
    {
        chessboard->stone[i/2+1]->alive=true;
        if (_str[i]=="*")
        {
            chessboard->stone[i/2+1]->alive=false;
            continue;
        }
        for (int j=0; j<10; j++)
        {
            if (_str[i]==d[j]) chessboard->stone[i/2+1]->x=(c[j]-1)*60+20;
            if (_str[i+1]==d[j]) chessboard->stone[i/2+1]->y=(c[j]-1)*60+20;
        }
    }
    if (!chessboard->stone[5]->alive)
    {
        gameover = new Gameover(this);
        gameover->setlabel("恭喜红方取得胜利");
        gameover->show();
        //timer->stop();
        isover=true;
    }
    if (!chessboard->stone[21]->alive)
    {
        gameover = new Gameover(this);
        gameover->setlabel("恭喜黑方取得胜利");
        gameover->show();
        isover=true;
        //timer->stop();
    }
   if (chessboard->isclient) chessboard->turn=1;
   chessboard->turn++;
   chessboard->repaint();

   if (!isover) timer->start(1000);




   bool jiangjun=false;
    int x2;
    int y2;

    for (int i=1; i<17; i++)
    {
        if (!chessboard->stone[i]->alive) continue;
        x2=0;
        y2=0;
        int g=0;
        for (int j=1; j<33; j++)
        {
            if(chessboard->stone[i]->x==chessboard->stone[21]->x && chessboard->stone[j]->x==chessboard->stone[i]->x &&((chessboard->stone[j]->y<chessboard->stone[21]->y && chessboard->stone[j]->y > chessboard->stone[i]->y) || (chessboard->stone[j]->y>chessboard->stone[21]->y && chessboard->stone[j]->y < chessboard->stone[i]->y)) ) y2++;
            if(chessboard->stone[i]->y==chessboard->stone[21]->y && chessboard->stone[j]->y==chessboard->stone[i]->y &&((chessboard->stone[j]->x<chessboard->stone[21]->x && chessboard->stone[j]->x > chessboard->stone[i]->x) || (chessboard->stone[j]->x>chessboard->stone[21]->x && chessboard->stone[j]->x < chessboard->stone[i]->x))) x2++;

        }
        if (chessboard->stone[i]->type=="blackche")
        {
            if (chessboard->stone[i]->x==chessboard->stone[21]->x && y2==0) jiangjun=true;
            if (chessboard->stone[i]->y==chessboard->stone[21]->y && x2==0) jiangjun=true;
        }
        if (chessboard->stone[i]->type=="blackma")
        {
            for (int j=1; j<33; j++){
                if((chessboard->stone[21]->x-chessboard->stone[i]->x==120 && chessboard->stone[j]->y==chessboard->stone[i]->y && chessboard->stone[j]->x-chessboard->stone[i]->x==60)||
                        (chessboard->stone[21]->x-chessboard->stone[i]->x==-120 && chessboard->stone[j]->y==chessboard->stone[i]->y && chessboard->stone[j]->x-chessboard->stone[i]->x==-60)||
                        (chessboard->stone[21]->y-chessboard->stone[i]->y==-120 && chessboard->stone[j]->x==chessboard->stone[i]->x && chessboard->stone[j]->y-chessboard->stone[i]->y==-60)||
                         (chessboard->stone[21]->y-chessboard->stone[i]->y==120 && chessboard->stone[j]->x==chessboard->stone[i]->x && chessboard->stone[j]->y-chessboard->stone[i]->y==60)) g=1;
            }
            if (g==0) if (chessboard->stone[i]->canmove(chessboard->stone[21]->x,chessboard->stone[21]->y)) jiangjun=true;


        }
        if (chessboard->stone[i]->type=="blackpao")
        {
            if (chessboard->stone[i]->x==chessboard->stone[21]->x && y2==1) jiangjun=true;
            if (chessboard->stone[i]->y==chessboard->stone[21]->y && x2==1) jiangjun=true;
        }
        if (chessboard->stone[i]->type=="blackbing")
        {
            if ( chessboard->stone[i]->canmove(chessboard->stone[21]->x,chessboard->stone[21]->y)) jiangjun=true;
        }
    }

    for (int i=17; i<33; i++)
    {
        if (!chessboard->stone[i]->alive) continue;
        x2=0;
        y2=0;
        int g=0;
        for (int j=1; j<33; j++)
        {
            if(chessboard->stone[i]->x==chessboard->stone[5]->x && chessboard->stone[j]->x==chessboard->stone[i]->x &&((chessboard->stone[j]->y<chessboard->stone[i]->y && chessboard->stone[j]->y > chessboard->stone[5]->y) || (chessboard->stone[j]->y>chessboard->stone[i]->y && chessboard->stone[j]->y < chessboard->stone[5]->y)) ) y2++;
            if(chessboard->stone[i]->y==chessboard->stone[5]->y && chessboard->stone[j]->y==chessboard->stone[i]->y &&((chessboard->stone[j]->x<chessboard->stone[i]->x && chessboard->stone[j]->x > chessboard->stone[5]->x) || (chessboard->stone[j]->x>chessboard->stone[i]->x && chessboard->stone[j]->x < chessboard->stone[5]->x))) x2++;

        }
        if (chessboard->stone[i]->type=="che")
        {
            if (chessboard->stone[i]->x==chessboard->stone[5]->x && y2==0) jiangjun=true;
            if (chessboard->stone[i]->y==chessboard->stone[5]->y && x2==0) jiangjun=true;
        }
        if (chessboard->stone[i]->type=="ma")
        {
            for(int j=1; j<33;j++){

                if ((chessboard->stone[5]->x-chessboard->stone[i]->x==120 && chessboard->stone[j]->y==chessboard->stone[i]->y && chessboard->stone[j]->x-chessboard->stone[i]->x==60)||
                        (chessboard->stone[5]->x-chessboard->stone[i]->x==-120 && chessboard->stone[j]->y==chessboard->stone[i]->y && chessboard->stone[j]->x-chessboard->stone[i]->x==-60)||
                        (chessboard->stone[5]->y-chessboard->stone[i]->y==-120 && chessboard->stone[j]->x==chessboard->stone[i]->x && chessboard->stone[j]->y-chessboard->stone[i]->y==-60)||
                        (chessboard->stone[5]->y-chessboard->stone[i]->y==120 && chessboard->stone[j]->x==chessboard->stone[i]->x && chessboard->stone[j]->y-chessboard->stone[i]->y==60)) g=1;
            }
            if (g==0) if (chessboard->stone[i]->canmove(chessboard->stone[5]->x,chessboard->stone[5]->y)) jiangjun=true;

        }
        if (chessboard->stone[i]->type=="pao")
        {
            if (chessboard->stone[i]->x==chessboard->stone[5]->x && y2==1) jiangjun=true;
            if (chessboard->stone[i]->y==chessboard->stone[5]->y && x2==1) jiangjun=true;
        }
        if (chessboard->stone[i]->type=="bing")
        {
            if ( chessboard->stone[i]->canmove(chessboard->stone[5]->x,chessboard->stone[5]->y)) jiangjun=true;
        }
    }

    if (jiangjun)
    {
        QSound::play(":/images/chessresource/jiangjun.wav");
    }




}

void MainWindow::giveup()
{
    gameover= new Gameover(this);
    gameover->setlabel("您投降了");
    gameover->show();
    QByteArray *array=new QByteArray;
    array->clear();
    array->append("giveup");
    this->socket->write(array->data());


}

void MainWindow::record()
{
    second--;
    if (second==0)
    {
        timer->stop();
        gameover= new Gameover(this);
        gameover->setlabel("您超时了");
        gameover->show();
        QByteArray *array=new QByteArray;
        array->clear();
        array->append("timeout");
        this->socket->write(array->data());
    }
    emit num(second);

}

void MainWindow::save()
{
    timer->stop();
    QString filename=QFileDialog::getSaveFileName(this,"saving","","*.txt");
    ofstream fout;
    fout.open(filename.toStdString());
    fout<< chessboard->str.toStdString();
    fout.close();
    timer->start(1000);

}

void MainWindow::restart()
{
   // if (chessboard!=nullptr) delete chessboard;
    //chessboard = new ChessBoard(this);
    chessboard->reset();
    chessboard->repaint();
  //  if(centralWidget()!=nullptr) delete centralWidget();
    //setCentralWidget(chessboard);

    second=10;
    emit num(10);
    chessboard->isclient=false;
    timer->start(1000);


}
void MainWindow::getload()
{
    timer->stop();
    QString filename;
    filename = QFileDialog::getOpenFileName(this,"文件","","text(*.txt)");
    ifstream fin;
    string canju;
    fin.open(filename.toStdString());
    fin>> canju;
    chessboard->str=QString::fromStdString(canju);
    int c[10]= {10,1,2,3,4,5,6,7,8,9};
    QString d="0123456789";
    for (int i=1; i<65; i=i+2)
    {
        if (chessboard->str[i]=="*")
        {
            chessboard->stone[i/2+1]->alive=false;
            continue;
        }
        for (int j=0; j<10; j++)
        {
            if (chessboard->str[i]==d[j]) chessboard->stone[i/2+1]->x=(c[j]-1)*60+20;
            if (chessboard->str[i+1]==d[j]) chessboard->stone[i/2+1]->y=(c[j]-1)*60+20;
        }
    }
    chessboard->repaint();
    chessboard->turn=1;
//    QByteArray *array=new QByteArray;

//    array->clear();
//    array->append(chessboard->str);
//    //array->append("abcd");
//    this->socket->write(array->data());
//    timer->start(1000);
}
