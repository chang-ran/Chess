#include "chessboard.h"
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QSound>

ChessBoard::ChessBoard(QWidget *parent) : QWidget(parent)
{

    stone[1] = new Stone(20,20,"blackche",false);
    stone[2] = new Stone(80,20,"blackma",false);
    stone[3] = new Stone(140,20,"blackxiang",false);
    stone[4] = new Stone(200,20,"blackshi",false);
    stone[5] = new Stone(260,20,"blackjiang",false);
    stone[6] = new Stone(320,20,"blackshi",false);
    stone[7] = new Stone(380,20,"blackxiang",false);
    stone[8] = new Stone(440,20,"blackma",false);
    stone[9] = new Stone(500,20,"blackche",false);
    stone[10] = new Stone(80,140,"blackpao",false);
    stone[11] = new Stone(440,140,"blackpao",false);
    stone[12] = new Stone(20,200,"blackbing",false);
    stone[13] = new Stone(140,200,"blackbing",false);
    stone[14] = new Stone(260,200,"blackbing",false);
    stone[15] = new Stone(380,200,"blackbing",false);
    stone[16] = new Stone(500,200,"blackbing",false);

    stone[17] = new Stone(20,560,"che");
    stone[18] = new Stone(80,560,"ma");
    stone[19] = new Stone(140,560,"xiang");
    stone[20] = new Stone(200,560,"shi");
    stone[21] = new Stone(260,560,"jiang");
    stone[22] = new Stone(320,560,"shi");
    stone[23] = new Stone(380,560,"xiang");
    stone[24] = new Stone(440,560,"ma");
    stone[25] = new Stone(500,560,"che");
    stone[26] = new Stone(80,440,"pao");
    stone[27] = new Stone(440,440,"pao");
    stone[28] = new Stone(20,380,"bing");
    stone[29] = new Stone(140,380,"bing");
    stone[30] = new Stone(260,380,"bing");
    stone[31] = new Stone(380,380,"bing");
    stone[32] = new Stone(500,380,"bing");
    turn=1;
    selected=0;
}

void ChessBoard::paintEvent(QPaintEvent *event)
{
    //qDebug()<<"paint";
    QPainter painter(this);
    QPixmap background;

    background.load(":/images/chessresource/background1.png");
    QBrush brush(QColor(211,191,154));
    painter.setBrush(brush);
    painter.drawRect(0,0,maximumWidth(),maximumHeight());
    painter.drawPixmap(49,50,480,540,background);



    for (int i=1; i<=32; i++)
    {
        images[i].load(":/images/chessresource/"+stone[i]->type);
        if (stone[i]->alive)painter.drawPixmap(stone[i]->x,stone[i]->y,60,60,images[i]);
    }


}

void ChessBoard::mousePressEvent(QMouseEvent *event)
{
    int x = event->pos().x();
    int y = event->pos().y();
    //qDebug()<<turn;
    if(turn%2!=0)
    {for(int i=1; i<17; i++) stone[i]->isturn=false;for(int i=17; i<33; i++) stone[i]->isturn=true;}
    else
    {for(int i=1; i<17; i++) stone[i]->isturn=true;for(int i=17; i<33; i++) stone[i]->isturn=false;}
    if (isclient)
    {for(int i=17; i<33; i++) stone[i]->isturn=false;}
    if (!isclient)
    {for(int i=1; i<17; i++) stone[i]->isturn=false;}

    if (selected==0)
    for (int i=1; i<33; i++)
    {
        if ((x-20)/60+1==stone[i]->X() && (y-20)/60+1== stone[i]->Y() && stone[i]->isturn && stone[i]->alive)
        {
            selected=1;
            chosen=i;
            qDebug()<< chosen;
        }

    }
    else
    {
        selected=0;
        int _x=(x-20)/60;
        int _y=(y-20)/60;
        _x=_x*60+20;
        _y=_y*60+20;
        //qDebug()<<_x<<","<<_y;
        //qDebug()<<stone[chosen]->x<<","<<stone[chosen]->y;
       // qDebug()<<stone[32]->x<<","<<stone[32]->y;
        int x1=0;
        int y1=0;
        bool you=false;
        for (int i=1; i<33; i++)
        {
            if(stone[i]->x==stone[chosen]->x && ((stone[i]->y<_y && stone[i]->y > stone[chosen]->y) || (stone[i]->y>_y && stone[i]->y < stone[chosen]->y)) ) y1++;
            if(stone[i]->y==stone[chosen]->y && ((stone[i]->x<_x && stone[i]->x > stone[chosen]->x) || (stone[i]->x>_x && stone[i]->x < stone[chosen]->x))) x1++;
            if (_x== stone[i]->x && _y==stone[i]->y) you=true;

        }

        for (int i=1; i<33; i++)
        {
            if (!stone[i]->alive) continue;
            if (_x== stone[i]->x && _y==stone[i]->y && stone[chosen]->isred==stone[i]->isred) return;
            if (stone[chosen]->type=="che"|| stone[chosen]->type=="blackche")
            {
                if(stone[i]->x==stone[chosen]->x && ((stone[i]->y<_y && stone[i]->y > stone[chosen]->y) || (stone[i]->y>_y && stone[i]->y < stone[chosen]->y)) ) {qDebug()<<1<<i;return;}
                if(stone[i]->y==stone[chosen]->y && ((stone[i]->x<_x && stone[i]->x > stone[chosen]->x) || (stone[i]->x>_x && stone[i]->x < stone[chosen]->x))) {qDebug()<<2<<i;return;}

            }

            if (stone[chosen]->type=="pao"|| stone[chosen]->type== "blackpao")
            {

                if (x1>1 || y1>1)return;
//qDebug()<<"p";
                if ((x1==1 || y1==1)&& !you) return;
//qDebug()<<"p";
                if ((x1==0 && y1==0) && you) return;
//qDebug()<<"p";
            }

            if (stone[chosen]->type =="ma"|| stone[chosen]->type=="blackma")
            {
                if ((_x-stone[chosen]->x==120 && stone[i]->y==stone[chosen]->y && stone[i]->x-stone[chosen]->x==60)||
                                        (_x-stone[chosen]->x==-120 && stone[i]->y==stone[chosen]->y && stone[i]->x-stone[chosen]->x==-60)||
                                        (_y-stone[chosen]->y==-120 && stone[i]->x==stone[chosen]->x && stone[i]->y-stone[chosen]->y==-60)||
                                        (_y-stone[chosen]->y==120 && stone[i]->x==stone[chosen]->x && stone[i]->y-stone[chosen]->y==60)) {qDebug()<<i;return;}
            }

            if (stone[chosen]->type =="xiang" || stone[chosen]->type=="blackxiang")
            {
                if (stone[i]->x==(stone[chosen]->x+_x)/2 && stone[i]->y==(stone[chosen]->y+_y)/2) {qDebug()<<i;return;}
            }


        }

        if((_x==stone[chosen]->x && _y==stone[chosen]->y) || !stone[chosen]->canmove(_x,_y)) return;

        for(int i=1; i<33; i++)
        {
            if(_x== stone[i]->x && _y==stone[i]->y && stone[chosen]->isred!=stone[i]->isred && stone[chosen]->canmove(_x,_y))
                stone[i]->alive=false;

        }

        stone[chosen]->x=_x;
        stone[chosen]->y=_y;


        turn++;
        int c[10]={10,1,2,3,4,5,6,7,8,9,};
        QString d="0123456789";
        str="*****************************************************************";
        for (int i=1; i<65; i=i+2)
        {
            for (int j=0; j<10; j++)
            {
                if (!stone[(i+1)/2]->alive) continue;
                else
                {
                    if (stone[(i+1)/2]->X()==c[j]) str[i]=d[j];
                    if (stone[(i+1)/2]->Y()==c[j]) str[i+1]=d[j];
                }
            }
        }
        emit sendstr();
        repaint();

       bool jiangjun=false;
        int x2;
        int y2;
        qDebug()<< "startjiangjun";
        for (int i=1; i<17; i++)
        {
            if (!stone[i]->alive) continue;
            x2=0;
            y2=0;
            int g=0;
            for (int j=1; j<33; j++)
            {
                if(stone[i]->x==stone[21]->x && stone[j]->x==stone[i]->x && ((stone[j]->y<stone[i]->y && stone[j]->y > stone[21]->y) || (stone[j]->y>stone[i]->y && stone[j]->y < stone[21]->y)) ) y2++;
                if(stone[i]->y==stone[21]->y && stone[j]->y==stone[i]->y && ((stone[j]->x<stone[i]->x && stone[j]->x > stone[21]->x) || (stone[j]->x>stone[i]->x && stone[j]->x < stone[21]->x))) x2++;


            }

            if (stone[i]->type=="blackche")
            {  // qDebug()<<x2<<","<<y2;
                if (stone[i]->x==stone[21]->x && y2==0) jiangjun=true;
                if (stone[i]->y==stone[21]->y && x2==0) jiangjun=true;
            }
            if (stone[i]->type=="blackma")
            {
                for (int j=1; j<33; j++){
                    if((stone[21]->x-stone[i]->x==120 && stone[j]->y==stone[i]->y && stone[j]->x-stone[i]->x==60)||
                            (stone[21]->x-stone[i]->x==-120 && stone[j]->y==stone[i]->y && stone[j]->x-stone[i]->x==-60)||
                            (stone[21]->y-stone[i]->y==-120 && stone[j]->x==stone[i]->x && stone[j]->y-stone[i]->y==-60)||
                            (stone[21]->y-stone[i]->y==120 && stone[j]->x==stone[i]->x && stone[j]->y-stone[i]->y==60)) g=1;
               }

                if (g==0)  if ( stone[i]->canmove(stone[21]->x,stone[21]->y) )jiangjun=true;


            }
            if (stone[i]->type=="blackpao")
            {
                if (stone[i]->x==stone[21]->x && y2==1) jiangjun=true;
                if (stone[i]->y==stone[21]->y && x2==1) jiangjun=true;
            }
            if (stone[i]->type=="blackbing")
            {
                if ((stone[21]->x-stone[i]->x)*(stone[21]->y-stone[i]->y)==0 && ((stone[21]->x-stone[i]->x)*(stone[21]->x-stone[i]->x)==3600 ||(stone[21]->y-stone[i]->y)*(stone[21]->y-stone[i]->y==3600)) && stone[i]->canmove(stone[21]->x,stone[21]->y)) jiangjun=true;
            }
        }



        for (int i=17; i<33; i++)
        {
            if (!stone[i]->alive) continue;
            x2=0;
            y2=0;
            int g=0;
            for (int j=1; j<33; j++)
            {
                if(stone[i]->x==stone[5]->x && stone[j]->x==stone[i]->x && ((stone[j]->y<stone[i]->y && stone[j]->y > stone[5]->y) || (stone[j]->y>stone[i]->y && stone[j]->y < stone[5]->y)) ) y2++;
                if(stone[i]->y==stone[5]->y && stone[j]->y==stone[i]->y && ((stone[j]->x<stone[i]->x && stone[j]->x > stone[5]->x) || (stone[j]->x>stone[i]->x && stone[j]->x < stone[5]->x))) x2++;


            }
            if (stone[i]->type=="che")
            {
                if (stone[i]->x==stone[5]->x && y2==0) jiangjun=true;
                if (stone[i]->y==stone[5]->y && x2==0) jiangjun=true;
            }
            if (stone[i]->type=="ma")
            {
                for (int j=1; j<33; j++){

                    if((stone[5]->x-stone[i]->x==120 && stone[j]->y==stone[i]->y && stone[j]->x-stone[i]->x==60)||
                         (stone[5]->x-stone[i]->x==-120 && stone[j]->y==stone[i]->y && stone[j]->x-stone[i]->x==-60)||
                         (stone[5]->y-stone[i]->y==-120 && stone[j]->x==stone[i]->x && stone[j]->y-stone[i]->y==-60)||
                         (stone[5]->y-stone[i]->y==120 && stone[j]->x==stone[i]->x && stone[j]->y-stone[i]->y==60)) g=1;

                }
                   if (g==0) if ( stone[i]->canmove(stone[5]->x,stone[5]->y)) jiangjun=true;


            }
            if (stone[i]->type=="pao")
            {
                if (stone[i]->x==stone[5]->x && y2==1) jiangjun=true;
                if (stone[i]->y==stone[5]->y && x2==1) jiangjun=true;
            }
            if (stone[i]->type=="bing")
            {
                qDebug()<<(stone[5]->x-stone[i]->x)*(stone[5]->x-stone[i]->x);
                qDebug()<<(stone[5]->y-stone[i]->y)*(stone[5]->y-stone[i]->y);
                if ((stone[5]->x-stone[i]->x)*(stone[5]->y-stone[i]->y)==0
                        && ((stone[5]->x-stone[i]->x)*(stone[5]->x-stone[i]->x)==3600
                            ||(stone[5]->y-stone[i]->y)*(stone[5]->y-stone[i]->y==3600))
                        && stone[i]->canmove(stone[5]->x,stone[5]->y)) jiangjun=true;
            }
        }

        if (jiangjun)
        {
            QSound::play(":/images/chessresource/jiangjun.wav");
        }

        if (!stone[5]->alive)
        {
            gameover = new Gameover(this);
            gameover->setlabel("恭喜红方取得胜利");
            gameover->show();
            emit over();

        }
        if (!stone[21]->alive)
        {
            gameover = new Gameover(this);
            gameover->setlabel("恭喜黑方取得胜利");
            gameover->show();
            emit over();
        }

    }

    //qDebug()<< x<<","<<y<<" "<<turn;
}

void ChessBoard::reset()
{
    stone[1] = new Stone(20,20,"blackche",false);
    stone[2] = new Stone(80,20,"blackma",false);
    stone[3] = new Stone(140,20,"blackxiang",false);
    stone[4] = new Stone(200,20,"blackshi",false);
    stone[5] = new Stone(260,20,"blackjiang",false);
    stone[6] = new Stone(320,20,"blackshi",false);
    stone[7] = new Stone(380,20,"blackxiang",false);
    stone[8] = new Stone(440,20,"blackma",false);
    stone[9] = new Stone(500,20,"blackche",false);
    stone[10] = new Stone(80,140,"blackpao",false);
    stone[11] = new Stone(440,140,"blackpao",false);
    stone[12] = new Stone(20,200,"blackbing",false);
    stone[13] = new Stone(140,200,"blackbing",false);
    stone[14] = new Stone(260,200,"blackbing",false);
    stone[15] = new Stone(380,200,"blackbing",false);
    stone[16] = new Stone(500,200,"blackbing",false);

    stone[17] = new Stone(20,560,"che");
    stone[18] = new Stone(80,560,"ma");
    stone[19] = new Stone(140,560,"xiang");
    stone[20] = new Stone(200,560,"shi");
    stone[21] = new Stone(260,560,"jiang");
    stone[22] = new Stone(320,560,"shi");
    stone[23] = new Stone(380,560,"xiang");
    stone[24] = new Stone(440,560,"ma");
    stone[25] = new Stone(500,560,"che");
    stone[26] = new Stone(80,440,"pao");
    stone[27] = new Stone(440,440,"pao");
    stone[28] = new Stone(20,380,"bing");
    stone[29] = new Stone(140,380,"bing");
    stone[30] = new Stone(260,380,"bing");
    stone[31] = new Stone(380,380,"bing");
    stone[32] = new Stone(500,380,"bing");
    turn=1;
    selected=0;
}


