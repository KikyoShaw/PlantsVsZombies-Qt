#ifndef ZBONUS_H
#define ZBONUS_H

#include <QWidget>
#include <QMovie>
#include <QMouseEvent>

#include "zObject.h"
#include "zScene.h"

class zBonus : public zObject
{
public:
    zBonus(QWidget* parent = 0);
    virtual void act();
};

class zSun : public zBonus
{
public:
    zSun(QWidget* parent = 0);
    ~zSun();
    void act();
    int frame;
    float level, speed, accelerate, x_speed = 0;
protected:
    void mousePressEvent(QMouseEvent *event);
private:
    QMovie* anim = new QMovie(":/Bonus/rc/Sun.gif");
};

class zSunFall : public zBonus
{
public:
    zSunFall(QWidget* parent = 0);
    ~zSunFall();
    void act();
    int frame;
    float level, speed;
protected:
    void mousePressEvent(QMouseEvent *event);
private:
    QMovie* anim = new QMovie(":/Bonus/rc/Sun.gif");
};

#endif // ZBONUS_H
