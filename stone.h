#ifndef STONE_H
#define STONE_H
#include <QString>
using namespace std;

class Stone
{
public:
    Stone(int _x, int _y, QString t, bool is=true, bool l=true);
    int X();
    int Y();
    int x,y;
    bool alive, isred,isturn;
    QString type;
    bool canmove(int a, int b);

};

#endif // STONE_H
