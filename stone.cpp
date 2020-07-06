#include "stone.h"
#include <QPainter>
#include <QDebug>

Stone::Stone(int _x, int _y, QString t, bool is , bool l):x(_x), y(_y), type(t), isred(is), alive(l)
{
    isturn=true;
}

int Stone::X()
{
    return (x-20)/60+1;
}

int Stone::Y()
{
    return (y-20)/60+1;
}


bool Stone::canmove(int a, int b)
{

    //qDebug()<<"a:"<<a<<",b:"<<b;
    //qDebug()<<a-x<<","<<b-y;
    if (a<20 || a>=560 || b <20 || b>= 620) return false;
    if (!isturn) return false;
    if (!alive) return false;
    if (type=="blackche" || type == "che" || type=="pao"||type=="blackpao")
    {
        if (a!=x && b!=y) return false;
    }
    if (type=="ma" || type == "blackma")
    {
        if (a-x>120 || a-x<-120 || b-y>120 || b-y<-120 || (a-x)*(b-y)==0) return false;

        if ((a-x)*(a-x)==3600 && (b-y)*(b-y)!=14400) return false;
        if ((a-x)*(a-x)==14400 && (b-y)*(b-y)!=3600) return false;
        //if((a-x==120 || a-x==-120) && (b-y!=60 || b-y!=60)) return false;

    }
    if (type=="xiang" || type=="blackxiang")
    {
        if (((a-x)/60)*((a-x)/60)!= 4 || ((b-y)/60)*((b-y)/60)!= 4) return false;
        if (isred)
            if (b< 260) return false;
        if (!isred)
            if (b> 320) return false;
    }
    if (type=="shi"|| type=="blackshi")
    {
        if((a-x)*(b-y)!=3600 && (a-x)*(b-y)!=-3600) return false;
        if (isred)
            if (a<200 || a> 320 || b<440) return false;
        if(!isred)
            if (a<200 || a> 320 || b>140) return false;

    }
    if (type=="jiang"|| type=="blackjiang")
    {
        if((a-x)*(b-y)!=0 || ((a-x)!=60 && (a-x)!=-60&& (b-y)!=60&& (b-y)!=-60)) return false;
        if (isred)
            if (a<200 || a> 320 || b<440) return false;
        if(!isred)
            if (a<200 || a> 320 || b>140) return false;
    }
    if (type=="bing"||type=="blackbing")
    {
        if((a-x)*(b-y)!=0 || ((a-x)!=60 && (a-x)!=-60&& (b-y)!=60&& (b-y)!=-60)) return false;
        if (isred)
            if(b-y>0)return false;
        if (!isred)
            if(b-y<0)return false;
    }
    return true;
}

