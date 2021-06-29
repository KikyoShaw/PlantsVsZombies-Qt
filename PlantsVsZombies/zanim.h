#ifndef ZANIM_H
#define ZANIM_H

#include <QWidget>
#include <QMovie>

#include "zObject.h"
#include "zScene.h"

class zAnim : public zObject
{
public:
    zAnim(QWidget* parent = 0);
    void act();
    int frame;
};

class zPeaHit : public zAnim
{
public:
    zPeaHit(QWidget* parent = 0);
    ~zPeaHit();
private:
    QMovie* anim = new QMovie(":/Anims/rc/PeaHit.gif");
};

class zFire : public zAnim
{
public:
    zFire(QWidget* parent = 0);
    ~zFire();
private:
    QMovie* anim = new QMovie(":/Anims/rc/Fire.gif");
};

class zZombieDie : public zAnim
{
public:
    zZombieDie(QWidget* parent = 0);
    ~zZombieDie();
private:
    QMovie* anim = new QMovie(":/Anims/rc/ZombieDie.gif");
};

class zBurnDie : public zAnim
{
public:
    zBurnDie(QWidget* parent = 0);
    ~zBurnDie();
private:
    QMovie* anim = new QMovie(":/Anims/rc/BurnDie.gif");
};

class zZombieHead : public zAnim
{
public:
    zZombieHead(QWidget* parent = 0);
    ~zZombieHead();
private:
    QMovie* anim = new QMovie(":/Anims/rc/ZombieHead.gif");
};

class zMashedPotato : public zAnim
{
public:
    zMashedPotato(QWidget* parent = 0);
    ~zMashedPotato();
private:
    QMovie* anim = new QMovie(":/Anims/rc/PotatoMine_mashed.gif");
};

class zBoom : public zAnim
{
public:
    zBoom(QWidget* parent = 0);
    ~zBoom();
private:
    QMovie* anim = new QMovie(":/Anims/rc/Boom.gif");
};

class zPoleZombieDie : public zAnim
{
public:
    zPoleZombieDie(QWidget* parent = 0);
    ~zPoleZombieDie();
private:
    QMovie* anim = new QMovie(":/Anims/rc/PoleZombieDie.gif");
};

class zPoleZombieHead : public zAnim
{
public:
    zPoleZombieHead(QWidget* parent = 0);
    ~zPoleZombieHead();
private:
    QMovie* anim = new QMovie(":/Anims/rc/PoleZombieHead.gif");
};

class zNewsDie : public zAnim
{
public:
    zNewsDie(QWidget* parent = 0);
    ~zNewsDie();
private:
    QMovie* anim = new QMovie(":/Anims/rc/NewsDie.gif");
};

class zNewsHead : public zAnim
{
public:
    zNewsHead(QWidget* parent = 0);
    ~zNewsHead();
private:
    QMovie* anim = new QMovie(":/Anims/rc/NewsHead.gif");
};

#endif // ZANIM_H
