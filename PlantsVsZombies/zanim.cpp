#include "zAnim.h"

zAnim::zAnim(QWidget* parent) : zObject(parent)
{

}

void zAnim::act()
{
    if ((this->frame) > 0)
    {
        this->frame --;
    }
    else
    {
        this->alive = false;
    }
}

zPeaHit::zPeaHit(QWidget* parent) : zAnim(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 2;
}

zPeaHit::~zPeaHit()
{
    delete (this->anim);
}

zFire::zFire(QWidget* parent) : zAnim(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 2;
}

zFire::~zFire()
{
    delete (this->anim);
}


zZombieDie::zZombieDie(QWidget* parent) : zAnim(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 50;
}

zZombieDie::~zZombieDie()
{
    delete (this->anim);
}

zBurnDie::zBurnDie(QWidget* parent) : zAnim(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 85;
}

zBurnDie::~zBurnDie()
{
    delete (this->anim);
}

zZombieHead::zZombieHead(QWidget* parent) : zAnim(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 40;
}

zZombieHead::~zZombieHead()
{
    delete (this->anim);
}

zMashedPotato::zMashedPotato(QWidget* parent) : zAnim(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 20;
}

zMashedPotato::~zMashedPotato()
{
    delete (this->anim);
}

zBoom::zBoom(QWidget* parent) : zAnim(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 40;
}

zBoom::~zBoom()
{
    delete (this->anim);
}

zPoleZombieDie::zPoleZombieDie(QWidget* parent) : zAnim(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 50;
}

zPoleZombieDie::~zPoleZombieDie()
{
    delete (this->anim);
}

zPoleZombieHead::zPoleZombieHead(QWidget* parent) : zAnim(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 40;
}

zPoleZombieHead::~zPoleZombieHead()
{
    delete (this->anim);
}

zNewsDie::zNewsDie(QWidget* parent) : zAnim(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 50;
}

zNewsDie::~zNewsDie()
{
    delete (this->anim);
}

zNewsHead::zNewsHead(QWidget* parent) : zAnim(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 40;
}

zNewsHead::~zNewsHead()
{
    delete (this->anim);
}
