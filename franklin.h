#ifndef FRANKLIN_H
#define FRANKLIN_H


#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>
#include <QTimer>
#include <QtMultimedia>
#include <QGraphicsView>
#include "thug.h"
#include "bullet.h"
#include "door.h"
#include "power.h"


//Please make sure to run the app at least once and then
// move all the assets to the project build file for the
// program to work correctly


class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int row, column;
    int data[17][23];
public:
    QGraphicsTextItem *ph;
    QGraphicsTextItem *state;
    QGraphicsTextItem *timetext;
    int health;
    bool invincible;
    Player(int boardData[17][23] , QGraphicsScene &scene);
    thug t1;
    thug t2;
    bullet b1;
    bullet b2;
    bullet b3;
    bullet b4;
    int cnt;
    door escape;
    QMediaPlayer* music;
    QAudioOutput* output;
    int enemies;
     bool timerready;
    power p1;
    power p2;
    int n;
     QTimer* stt;
     QTimer* sttb;
     QTimer *displayt;
    void updatehealth();
    void endgame();
    void victory();
    void level2();
     void level3();
    bool lvl2;
       bool lvl3;
       int lvlnum;
        QGraphicsTextItem *lvl;
    QGraphicsPixmapItem bi2[17][23];

public slots:
    void keyPressEvent(QKeyEvent* event);
    void imagereset();
    void imagereset1();
    void imagereset2();
    void imagereset3();
    void statereset();
    void statereset1();
    void display();





};



#endif // FRANKLIN_H
