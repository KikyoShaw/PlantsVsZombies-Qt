#ifndef ZFLYINGOBJECT_H
#define ZFLYINGOBJECT_H

#include <QWidget>
#include <QMovie>

#include "zObject.h"
#include "zScene.h"
#include "zAnim.h"

class zFlyingObject : public zObject
{
public:
    zFlyingObject(QWidget* parent = 0);
    virtual void act();
    int raw;
    bool canFire = false;
};

class zPea : public zFlyingObject
{
public:
    zPea(QWidget* parent = 0);
    ~zPea();
    void act();
private:
    QMovie* anim = new QMovie(":/FlyingObjects/rc/Pea.gif");
    int speed;
};

class zFirePea : public zFlyingObject
{
public:
    zFirePea(QWidget* parent = 0);
    ~zFirePea();
    void act();
private:
    QMovie* anim = new QMovie(":/FlyingObjects/rc/PeaFire.gif");
    int speed;
};

class zIcePea : public zFlyingObject
{
public:
    zIcePea(QWidget* parent = 0);
    ~zIcePea();
    void act();
private:
    QMovie* anim = new QMovie(":/FlyingObjects/rc/PeaIce.gif");
    int speed;
};

class zMush : public zFlyingObject
{
public:
    zMush(QWidget* parent = 0);
    ~zMush();
    void act();
private:
    QMovie* anim = new QMovie(":/FlyingObjects/rc/Mush.gif");
    int speed;
    int TimerFly;
};

#endif // ZFLYINGOBJECT_H
