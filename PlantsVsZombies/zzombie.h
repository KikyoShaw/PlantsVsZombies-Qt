#ifndef ZZOMBIE_H
#define ZZOMBIE_H

#include <QLabel>
#include <QMovie>
#include <QDebug>
#include <QMouseEvent>

#include "zObject.h"
#include "zScene.h"

//Base Class

class zZombie : public zObject
{
    Q_OBJECT
public:
    zZombie(QWidget* parent = 0);
    virtual void act();
    virtual void hit(int damage, bool silence = false);
    virtual void ice();
    int raw;
    int offset = 0;
    int eatFrame = 0;
    bool iced = false;
    bool shield = false;
    float speed;
};

class zCommonZombie : public zZombie
{
    Q_OBJECT
public:
    zCommonZombie(QWidget* parent = 0, int type = 0);
    ~zCommonZombie();
    void act();
    void hit(int damage, bool silence = false);
    void ice();
private:
    QMovie* walk = nullptr;
    QMovie* attack = nullptr;
    QMovie* prop_walk = nullptr;
    QMovie* prop_attack = nullptr;
    bool prop, iron;
    int prop_strength;
    float xpos;
};

class zPoleZombie : public zZombie
{
    Q_OBJECT
public:
    zPoleZombie(QWidget* parent = 0);
    ~zPoleZombie();
    void act();
    void hit(int damage, bool silence = false);
    void ice();
private:
    QMovie* walk = new QMovie(":/Zombies/rc/PoleZombieWalk.gif");
    QMovie* attack = new QMovie(":/Zombies/rc/PoleZombieAttack.gif");
    QMovie* run = new QMovie(":/Zombies/rc/PoleZombie.gif");
    QMovie* jump_1 = new QMovie(":/Zombies/rc/PoleZombieJump.gif");
    QMovie* jump_2 = new QMovie(":/Zombies/rc/PoleZombieJump2.gif");
    bool poled = true;
    bool jumping = false, jumping_1 = false;
    float xpos;
};

class zNewsZombie : public zZombie
{
    Q_OBJECT
public:
    zNewsZombie(QWidget* parent = 0);
    ~zNewsZombie();
    void act();
    void hit(int damage, bool silence = false);
    void ice();
private:
    QMovie* walk = new QMovie(":/Zombies/rc/NewsWalk.gif");
    QMovie* attack = new QMovie(":/Zombies/rc/NewsAttack.gif");
    QMovie* paper_walk = new QMovie(":/Zombies/rc/NewsWalk_1.gif");
    QMovie* paper_attack = new QMovie(":/Zombies/rc/NewsAttack_1.gif");
    QMovie* lose_paper = new QMovie(":/Zombies/rc/NewsLost.gif");
    bool paper = true;
    bool angrying = false;
    float xpos;
    int paper_strength;
};

#endif // ZZOMBIE_H
