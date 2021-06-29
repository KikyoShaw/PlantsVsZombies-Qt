#ifndef ZSCENE_H
#define ZSCENE_H

#include <QLabel>
#include <QPushButton>
#include <QMovie>
#include <QTimer>
#include <QDebug>
#include <QMouseEvent>
#include <QKeyEvent>

#include "zObject.h"
#include "zPlant.h"
#include "zZombie.h"
#include "zFlyingObject.h"
#include "zAnim.h"
#include "zBonus.h"
#include "zCard.h"

class zObject;
class zPlant;
class zZombie;
class zFlyingObject;
class zAnim;
class zBonus;
class zCard;

class zScene : public zObject
{
    Q_OBJECT
public:
    explicit zScene(QWidget* parent = 0);
    ~zScene();
    QPoint getCell();

    QList<zZombie*> Zombies;
    QList<zPlant*> Plants;
    QList<zFlyingObject*> FlyingObjects;
    QList<zAnim*> Anims;
    QList<zBonus*> Bonuses;
    QList<zCard*> Cards;

    QPoint m;
    QPoint cellSize = QPoint(1, 1);
    QRect rect = QRect(0, 0, 1, 1);
    QRect screen = QRect(170, 0, 900, 600);

    QTimer* timer = nullptr;
    QSound* music = nullptr;
    QLabel* SunFront = new QLabel(this);
    QLabel* SunBack = new QLabel(this);
    QMovie* sunback = new QMovie(":/Interface/rc/SunBack.png");        //backgroud of value of sun



    void removeDeath();            //remove dead item
    void act();
    void createZombie();
    void judge();
    virtual void uiSetup();
    void putPlant(QPoint t_cell);
    void putZombie(int raw, int type);

    bool hasEnemy[6];
    int sunPoint = 50;
    int tempSunPoint;
    int threat = 0;
    int TimerLose = 0;
    zCard* currentCard = nullptr;
    QPoint currentPos;
protected:
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
signals:
    void toTitle();
    void toLawn();
    void toDarkLawn();
};

class zLawnScene : public zScene
{
    Q_OBJECT
public:
    explicit zLawnScene(QWidget* parent = 0);
    ~zLawnScene();
protected:
    void keyPressEvent(QKeyEvent *event);
private:
    QMovie* background = new QMovie(":/Background/rc/background1.jpg");
    QPushButton* exit = new QPushButton(this);
    QPoint cell;
    void uiSetup();
private slots:
    void onTimer();
    void leave();
};

class zDarkScene : public zScene
{
    Q_OBJECT
public:
    explicit zDarkScene(QWidget* parent = 0);
    ~zDarkScene();
protected:
    void keyPressEvent(QKeyEvent *event);
private:
    QMovie* background = new QMovie(":/Background/rc/background2.jpg");
    QPushButton* exit = new QPushButton(this);
    QPoint cell;
    void uiSetup();
private slots:
    void onTimer();
    void leave();
};

class zStartScene : public zScene
{
    Q_OBJECT
public:
    explicit zStartScene(QWidget* parent = 0);
    ~zStartScene();
private:
    QMovie* background = new QMovie(":/Background/rc/Title.jpg");
    QMovie* lawn = new QMovie(":/Interface/rc/zombatar_background_crazydave.png");
    QMovie* dark = new QMovie(":/Interface/rc/zombatar_background_menu.png");
    QLabel* btn1 = new QLabel(this);
    QLabel* btn2 = new QLabel(this);
    QLabel* title = new QLabel(this);
    QLabel* UserName = new QLabel(this);
    QLabel* BestTime = new QLabel(this);
protected:
    void mousePressEvent(QMouseEvent *event);
};

class zStartScreen : public zScene
{
    Q_OBJECT
public:
    explicit zStartScreen(QWidget* parent = 0);
    ~zStartScreen();
private:
    QMovie* background = new QMovie(":/Interface/rc/StartScreen.jpg");
    QWidget* front = new QWidget(this);
    int frame = 100;
private slots:
    void onTimer();
};

#endif // ZSCENE_H
