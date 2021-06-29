#ifndef ZPLANT_H
#define ZPLANT_H

#include <QLabel>
#include <QMovie>
#include <QDebug>
#include <QSound>
#include <QMouseEvent>

#include "zObject.h"
#include "zScene.h"
#include "zFlyingObject.h"

//Base Class

class zPlant : public zObject
{
    Q_OBJECT
public:
    zPlant(QWidget* parent = 0);
    virtual void act();
    virtual void hit(int damage);
    int raw, column;
};

//Pea Shooter

class zPeaShooter : public zPlant
{
    Q_OBJECT
public:
    zPeaShooter(QWidget* parent = 0);
    ~zPeaShooter();
    void act();
private:
    QMovie* anim = new QMovie(":/Plants/rc/Peashooter.gif");
    int TimerShoot, TimerShoot_max;
};

//SunFlower

class zSunFlower : public zPlant
{
    Q_OBJECT
public:
    zSunFlower(QWidget* parent = 0);
    ~zSunFlower();
    void act();
private:
    QMovie* anim = new QMovie(":/Plants/rc/SunFlower.gif");
    int TimerSun, TimerSun_max;
};

//WallNut

class zWallNut : public zPlant
{
    Q_OBJECT
public:
    zWallNut(QWidget* parent = 0);
    ~zWallNut();
    void act();
private:
    QMovie* anim = new QMovie(":/Plants/rc/WallNut.gif");
    QMovie* anim_1 = new QMovie(":/Plants/rc/Wallnut_1.gif");
    QMovie* anim_2 = new QMovie(":/Plants/rc/Wallnut_2.gif");
};

//Repeater

class zRepeater : public zPlant
{
    Q_OBJECT
public:
    zRepeater(QWidget* parent = 0);
    ~zRepeater();
    void act();
private:
    QMovie* anim = new QMovie(":/Plants/rc/Repeater.gif");
    int TimerShoot, TimerShoot_max;
};

class zPotatoMine : public zPlant
{
    Q_OBJECT
public:
    zPotatoMine(QWidget* parent = 0);
    ~zPotatoMine();
    void act();
private:
    QMovie* anim = new QMovie(":/Plants/rc/PotatoMine_1.gif");
    QMovie* anim_1 = new QMovie(":/Plants/rc/PotatoMine.gif");
    int TimerGrow;
};

class zFireTree : public zPlant
{
    Q_OBJECT
public:
    zFireTree(QWidget* parent = 0);
    ~zFireTree();
    void act();
private:
    QMovie* anim = new QMovie(":/Plants/rc/FireTree.gif");
};

class zCherryBomb : public zPlant
{
    Q_OBJECT
public:
    zCherryBomb(QWidget* parent = 0);
    ~zCherryBomb();
    void act();
private:
    QMovie* anim = new QMovie(":/Plants/rc/CherryBomb.gif");
    int TimerBoom;
};


class zIcePeaShooter : public zPlant
{
    Q_OBJECT
public:
    zIcePeaShooter(QWidget* parent = 0);
    ~zIcePeaShooter();
    void act();
private:
    QMovie* anim = new QMovie(":/Plants/rc/IcePeaShooter.gif");
    int TimerShoot, TimerShoot_max;
};


class zMushroom : public zPlant
{
    Q_OBJECT
public:
    zMushroom(QWidget* parent = 0);
    ~zMushroom();
    void act();
private:
    QMovie* anim = new QMovie(":/Plants/rc/Mushroom.gif");
    int TimerShoot, TimerShoot_max;
};
#endif // ZPLANT_H
