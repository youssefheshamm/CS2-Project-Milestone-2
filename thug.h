#ifndef THUG_H
#define THUG_H
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>
#include <iostream>
#include <stack>
#include <set>
#include <limits>

using namespace std;
//Please make sure to run the app at least once and then
// move all the assets to the project build file for the
// program to work correctly

class thug : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:



public:
    int map[17][23];
    int counter;
     int row, column;
    thug();
    void setthug(int mapData[17][23], int r, int c);
    int health;
    bool die;
    void setpng( QPixmap npc);
void resetpos(int r, int c);
public slots:
      void move(int pr, int pc);

};
#endif // THUG_H
