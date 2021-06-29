#include "zBonus.h"

zBonus::zBonus(QWidget* parent) : zObject(parent)
{

}

void zBonus::act()
{

}

zSun::zSun(QWidget* parent) : zBonus(parent)
{
    this->setGeometry(260, 80, 80, 80);
    this->setMovie(anim);
    anim->start();
    this->show();
    this->speed = -(qrand() % 5 + 7);
    this->accelerate = 2;
    this->level = 200;
    this->x_speed = qrand() % 5 - 2;
    this->frame = 750;
}

zSun::~zSun()
{
    delete (this->anim);
}

void zSun::act()
{
    this->raise();
    this->frame --;
    if (this->frame <= 0)
    {
        this->alive = false;
    }
    if (this->y() <= this->level)
    {
        this->speed += this->accelerate;
        this->move(this->x() + this->x_speed, this->y() + this->speed);
    }
}

void zSun::mousePressEvent(QMouseEvent* event)
{
    this->alive = false;
    scene->sunPoint += 25;
    QSound::play(":/Sounds/rc/Sun.wav");
}

zSunFall::zSunFall(QWidget* parent) : zBonus(parent)
{
    this->setGeometry(qrand() % 600 + 320, 0, 80, 80);
    this->setMovie(anim);
    anim->start();
    this->show();
    this->speed = 2;
    this->level = qrand() % 400 + 100;
    this->frame = 750;
}

zSunFall::~zSunFall()
{
    delete (this->anim);
}

void zSunFall::act()
{
    this->raise();
    this->frame --;
    if (this->frame <= 0)
    {
        this->alive = false;
    }
    if (this->y() <= this->level)
    {
        this->move(this->x(), this->y() + this->speed);
    }
}

void zSunFall::mousePressEvent(QMouseEvent* event)
{
    this->alive = false;
    scene->sunPoint += 25;
    QSound::play(":/Sounds/rc/Sun.wav");
}
