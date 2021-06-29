#include "zzombie.h"

zZombie::zZombie(QWidget* parent) : zObject(parent)
{

}

void zZombie::act()
{

}

void zZombie::hit(int damage, bool silence)
{

}

void zZombie::ice()
{

}

//Type: 0 for Common Zombie
//      1 for Flag Zombie
//      2 for Cone Zombie
//      3 for Bucket Zombie
//      4 for Shield Zombie
zCommonZombie::zCommonZombie(QWidget* parent, int type) : zZombie(parent)
{
    switch (qrand() % 2)
    {
    case 0:
        this->walk = new QMovie(":/Zombies/rc/Zombie.gif");
        break;
    case 1:
        this->walk = new QMovie(":/Zombies/rc/Zombie_2.gif");
        break;
    }
    this->attack = new QMovie(":/Zombies/rc/ZombieAttack.gif");
    switch (type)
    {
    case 0:
        this->prop = false;
        this->iron = false;
        break;
    case 1:
        this->prop = false;
        this->iron = false;
        this->offset = 20;
        delete this->walk;
        delete this->attack;
        this->walk = new QMovie(":/Zombies/rc/ZombieFlag.gif");
        this->attack = new QMovie(":/Zombies/rc/ZombieFlagAttack.gif");
        break;
    case 2:
        this->prop = true;
        this->iron = false;
        this->prop_strength = 200;
        this->prop_walk = new QMovie(":/Zombies/rc/ZombieCone.gif");
        this->prop_attack = new QMovie(":/Zombies/rc/ZombieConeAttack.gif");
        this->offset = 20;
        break;
    case 3:
        this->prop = true;
        this->iron = true;
        this->prop_strength = 400;
        this->prop_walk = new QMovie(":/Zombies/rc/ZombieBucket.gif");
        this->prop_attack = new QMovie(":/Zombies/rc/ZombieBucketAttack.gif");
        break;
    case 4:
        this->prop = true;
        this->iron = true;
        this->shield = true;
        this->prop_strength = 400;
        this->prop_walk = new QMovie(":/Zombies/rc/ZombieShield.gif");
        this->prop_attack = new QMovie(":/Zombies/rc/ZombieShieldAttack.gif");
        break;
    }
    this->speed = 0.25;
    this->strength = 200;
    this->xpos = 950;
    if (this->prop)
    {
        this->setMovie(this->prop_walk);
        this->walk->start();
        this->prop_walk->start();
        this->attack->start();
        this->prop_attack->start();
    }
    else
    {
        this->setMovie(this->walk);
        this->walk->start();
        this->attack->start();
    }
    this->show();
}

zCommonZombie::~zCommonZombie()
{
    delete (this->walk);
    delete (this->attack);
}

void zCommonZombie::act()
{
    this->raise();
    zPlant* plant;
    foreach (plant, this->scene->Plants)
    {
        if ((qAbs(plant->x() - this->x() - 55 - this->offset) < 40) && ((this->raw) == (plant->raw)) && (this->alive))
        {
            if (this->eatFrame <= 0)
            {
                QSound::play(":/Sounds/rc/Eat.wav");
                this->eatFrame = 20;
            }
            this->eatFrame --;
            if (this->prop)
            {
                this->setMovie(this->prop_attack);
            }
            else
            {
                this->setMovie(this->attack);
            }
            plant->hit(1);
            return;
        }
    }
    if (this->prop)
    {
        this->setMovie(this->prop_walk);
    }
    else
    {
        this->setMovie(this->walk);
    }
    this->xpos -= this->speed;
    this->move(this->xpos, this->y());
}

void zCommonZombie::hit(int damage, bool silence)
{
    if (damage >= 200)
    {
        this->alive = false;
        zAnim* death_anim = new zBurnDie(scene);
        death_anim->setGeometry(this->x() - 30, this->y() + 25, 180, 150);
        this->scene->Anims.append(death_anim);
        if (!(this->prop_walk == nullptr))
        {
            delete this->prop_walk;
        }
        if (!(this->prop_attack == nullptr))
        {
            delete this->prop_attack;
        }
        return;
    }
    if (!(silence))
    {
        if ((this->prop) && (this->iron))
        {
            QSound::play(":/Sounds/rc/ShieldHit.wav");
        }
        else
        {
            QSound::play(":/Sounds/rc/Pea.wav");
        }
    }
    if (this->prop)
    {
        this->prop_strength -= damage;
        if (this->prop_strength <= 0)
        {
            this->prop = false;
            this->xpos += this->offset;
            this->act();
            this->setMovie(this->walk);
            this->walk->start();
            delete this->prop_walk;
            delete this->prop_attack;
            this->prop_walk = nullptr;
            this->prop_attack = nullptr;
            this->shield = false;
        }
    }
    else
    {
        this->strength -= damage;
    }
    if (this->strength <= 0)
    {
        this->alive = false;
        zAnim* death_anim = new zZombieDie(scene);
        death_anim->setGeometry(this->x() - 30, this->y() + 25, 180, 150);
        this->scene->Anims.append(death_anim);
        zAnim* death_head = new zZombieHead(scene);
        death_head->setGeometry(this->x() + 50, this->y() + 25, 180, 200);
        this->scene->Anims.append(death_head);
    }
}

void zCommonZombie::ice()
{
    if ((!iced) && (!shield))
    {
        this->iced = true;
        this->speed /= 2;
        if (!(this->walk == nullptr))
        {
            this->walk->setSpeed(50);
        }
        if (!(this->attack == nullptr))
        {
            this->attack->setSpeed(50);
        }
        if (!(this->prop_walk == nullptr))
        {
            this->prop_walk->setSpeed(50);
        }
        if (!(this->prop_attack == nullptr))
        {
            this->prop_attack->setSpeed(50);
        }
    }
}



zPoleZombie::zPoleZombie(QWidget* parent) : zZombie(parent)
{
    this->setMovie(this->run);
    this->run->start();
    this->walk->start();
    this->attack->start();
    this->speed = 0.5;
    this->strength = 200;
    this->xpos = 950;
    this->show();
    this->offset = 145;
}

zPoleZombie::~zPoleZombie()
{
    delete this->walk;
    delete this->attack;
    delete this->run;
    delete this->jump_1;
    delete this->jump_2;
}

void zPoleZombie::act()
{
    this->raise();
    zPlant* plant;
    if (this->jumping_1)
    {
        if (this->jump_2->currentFrameNumber() >= (this->jump_2->frameCount() - 1))
        {
            this->jump_2->stop();
            this->jumping_1 = false;
            this->speed /= 2;
        }
        return;
    }
    else if ((this->jumping) && (this->jump_1->currentFrameNumber() == (this->jump_1->frameCount() - 1)) && !(this->jumping_1))
    {
        this->jump_1->stop();
        this->setMovie(this->jump_2);
        this->jump_2->start();
        this->xpos -= 110;
        this->move(this->xpos, this->y());
        this->jumping_1 = true;
        this->jumping = false;
        return;
    }
    else if (this->jumping)
    {
        return;
    }
    foreach (plant, this->scene->Plants)
    {
        if ((qAbs(plant->x() - this->x() - 55 - this->offset) < 40) && ((this->raw) == (plant->raw)) && (this->alive))
        {
            if (this->poled)
            {
                this->poled = false;
                this->jumping = true;
                this->setMovie(this->jump_1);
                this->jump_1->start();
                QSound::play(":/Sounds/rc/Pole.wav");
                return;
            }
            else
            {
                if (this->eatFrame <= 0)
                {
                    QSound::play(":/Sounds/rc/Eat.wav");
                    this->eatFrame = 20;
                }
                this->eatFrame --;
                this->setMovie(this->attack);
                plant->hit(1);
                return;
            }
        }
    }
    if (this->poled)
    {
        this->setMovie(this->run);
    }
    else
    {
        this->setMovie(this->walk);
    }
    this->xpos -= this->speed;
    this->move(this->xpos, this->y());
}

void zPoleZombie::hit(int damage, bool silence)
{
    if (damage >= 200)
    {
        this->alive = false;
        zAnim* death_anim = new zBurnDie(scene);
        death_anim->setGeometry(this->x() - 20 + this->offset, this->y() + 25, 180, 150);
        this->scene->Anims.append(death_anim);
        return;
    }
    if (!(silence))
    {
        QSound::play(":/Sounds/rc/Pea.wav");
    }
    this->strength -= damage;
    if (this->strength <= 0)
    {
        this->alive = false;
        zAnim* death_anim = new zPoleZombieDie(scene);
        death_anim->setGeometry(this->x() - 30, this->y(), 300, 200);
        this->scene->Anims.append(death_anim);
        zAnim* death_head = new zPoleZombieHead(scene);
        death_head->setGeometry(this->x(), this->y() - 50, 300, 300);
        this->scene->Anims.append(death_head);
    }
}

void zPoleZombie::ice()
{
    if (!iced)
    {
        this->iced = true;
        this->speed /= 2;
        this->walk->setSpeed(50);
        this->attack->setSpeed(50);
        this->jump_1->setSpeed(50);
        this->jump_2->setSpeed(50);
        this->run->setSpeed(50);
    }
}



zNewsZombie::zNewsZombie(QWidget* parent) : zZombie(parent)
{
    this->setMovie(this->paper_walk);
    this->paper_walk->start();
    this->walk->start();
    this->attack->start();
    this->paper_attack->start();
    this->speed = 0.25;
    this->strength = 200;
    this->paper_strength = 50;
    this->xpos = 950;
    this->show();
    //this->offset = 145;
}

zNewsZombie::~zNewsZombie()
{
    delete this->walk;
    delete this->attack;
    delete this->paper_walk;
    delete this->paper_attack;
    delete this->lose_paper;
}

void zNewsZombie::act()
{
    this->raise();
    zPlant* plant;
    if (this->angrying)
    {
        if (this->lose_paper->currentFrameNumber() >= (this->lose_paper->frameCount() - 1))
        {
            this->lose_paper->stop();
            this->angrying = false;
            this->speed *= 2;
            QSound::play(":/Sounds/rc/NewsLost.wav");
        }
        return;
    }
    foreach (plant, this->scene->Plants)
    {
        if ((qAbs(plant->x() - this->x() - 55 - this->offset) < 40) && ((this->raw) == (plant->raw)) && (this->alive))
        {
            if (this->angrying)
            {
                return;
            }
            else
            {
                if (this->eatFrame <= 0)
                {
                    QSound::play(":/Sounds/rc/Eat.wav");
                    this->eatFrame = 27;
                }
                this->eatFrame --;
                if (this->paper)
                {
                    this->setMovie(this->paper_attack);
                    plant->hit(1);
                }
                else
                {
                    this->setMovie(this->attack);
                    plant->hit(2);
                }
                return;
            }
        }
    }
    if (this->paper)
    {
        this->setMovie(this->paper_walk);
    }
    else
    {
        this->setMovie(this->walk);
    }
    this->xpos -= this->speed;
    this->move(this->xpos, this->y());
}

void zNewsZombie::hit(int damage, bool silence)
{
    if (damage >= 200)
    {
        this->alive = false;
        zAnim* death_anim = new zBurnDie(scene);
        death_anim->setGeometry(this->x() - 20 + this->offset, this->y() + 25, 180, 150);
        this->scene->Anims.append(death_anim);
        return;
    }
    if (!(silence))
    {
        QSound::play(":/Sounds/rc/Pea.wav");
    }
    if (this->paper)
    {
        this->paper_strength -= damage;
        if (this->paper_strength <= 0)
        {
            this->paper = false;
            this->angrying = true;
            this->setMovie(this->lose_paper);
            this->lose_paper->start();
        }
    }
    else
    {
        this->strength -= damage;
        if (this->strength <= 0)
        {
            this->alive = false;
            zAnim* death_anim = new zNewsDie(scene);
            death_anim->setGeometry(this->x() - 30, this->y() + 25, 180, 150);
            this->scene->Anims.append(death_anim);
            zAnim* death_head = new zNewsHead(scene);
            death_head->setGeometry(this->x() + 50, this->y() + 25, 180, 200);
            this->scene->Anims.append(death_head);
        }
    }
}

void zNewsZombie::ice()
{
    if (!iced)
    {
        this->iced = true;
        this->speed /= 2;
        this->walk->setSpeed(50);
        this->attack->setSpeed(50);
        this->paper_walk->setSpeed(50);
        this->paper_attack->setSpeed(50);
        this->lose_paper->setSpeed(50);
    }
}
