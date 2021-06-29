#include "zPlant.h"

zPlant::zPlant(QWidget *parent) : zObject(parent)
{

}

void zPlant::act()
{

}

void zPlant::hit(int damage)
{
    this->strength -= damage;
    if (this->strength <= 0)
    {
        this->alive = false;
    }
}



zPeaShooter::zPeaShooter(QWidget *parent) : zPlant(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->TimerShoot_max = 50;
    this->TimerShoot = this->TimerShoot_max;
    this->strength = 200;
}

void zPeaShooter::act()
{
    if (this->TimerShoot <= 0)
    {
        if (!(scene->hasEnemy[this->raw]))
        {
            this->TimerShoot = qrand() % 20;// not to shoot too many peas in a single timer event
            return;
        }
        this->TimerShoot = this->TimerShoot_max;
        zPea* pea = new zPea(scene);
        pea->setGeometry(this->x() + 20, this->y() + 15 - (qrand() % 5), 80, 40);
        pea->raw = this->raw;
        scene->FlyingObjects.append(pea);
        QSound::play(":/Sounds/rc/PeaHit.wav");
    }
    else
    {
        this->TimerShoot --;
    }
}

zPeaShooter::~zPeaShooter()
{
    delete this->anim;
}



zSunFlower::zSunFlower(QWidget *parent) : zPlant(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->TimerSun_max = 500;
    this->TimerSun = qrand() % this->TimerSun_max;
    this->strength = 200;
}

void zSunFlower::act()
{
    if (this->TimerSun <= 0)
    {
        this->TimerSun = this->TimerSun_max;
        zSun* sun = new zSun(scene);
        sun->setGeometry(this->x(), this->y() + 15 - (qrand() % 5), 80, 80);
        sun->level = this->y() + 40;
        scene->Bonuses.append(sun);
        //QSound::play(":/Sounds/rc/PeaHit.wav");
    }
    else
    {
        this->TimerSun --;
    }
}

zSunFlower::~zSunFlower()
{
    delete this->anim;
}



zWallNut::zWallNut(QWidget *parent) : zPlant(parent)
{
    this->setMovie(anim);
    anim->start();
    anim_1->start();
    anim_2->start();
    this->show();
    this->strength = 1200;
}

void zWallNut::act()
{
    if ((this->strength < 800) && (this->strength >= 800))
    {
        this->setMovie(anim_1);
    }
    if (this->strength < 400)
    {
        this->setMovie(anim_2);
    }
}

zWallNut::~zWallNut()
{
    delete this->anim;
    delete this->anim_1;
    delete this->anim_2;
}



zRepeater::zRepeater(QWidget *parent) : zPlant(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->TimerShoot_max = 50;
    this->TimerShoot = this->TimerShoot_max;
    this->strength = 200;
}

void zRepeater::act()
{
    if (this->TimerShoot <= 0)
    {
        if (!(scene->hasEnemy[this->raw]))
        {
            this->TimerShoot = qrand() % 20;// not to shoot too many peas in a single timer event
            return;
        }
        this->TimerShoot = this->TimerShoot_max;
        zPea* pea = new zPea(scene);
        pea->setGeometry(this->x() + 20, this->y() + 15 - (qrand() % 5), 80, 40);
        pea->raw = this->raw;
        scene->FlyingObjects.append(pea);
        QSound::play(":/Sounds/rc/PeaHit.wav");
    }
    else if (this->TimerShoot == 5)
    {
        if (!(scene->hasEnemy[this->raw]))
        {
            this->TimerShoot = qrand() % 20;// not to shoot too many peas in a single timer event
            return;
        }
        zPea* pea = new zPea(scene);
        pea->setGeometry(this->x() + 20, this->y() + 15 - (qrand() % 5), 80, 40);
        pea->raw = this->raw;
        scene->FlyingObjects.append(pea);
        QSound::play(":/Sounds/rc/PeaHit.wav");
        this->TimerShoot --;
    }
    else
    {
        this->TimerShoot --;
    }
}

zRepeater::~zRepeater()
{
    delete this->anim;
}



zPotatoMine::zPotatoMine(QWidget *parent) : zPlant(parent)
{
    this->setMovie(anim);
    anim->start();
    anim_1->start();
    this->show();
    this->strength = 200;
    this->TimerGrow = 800;
}

void zPotatoMine::act()
{
    if (this->TimerGrow > 0)
    {
        this->TimerGrow --;
    }
    else
    {
        this->setMovie(anim_1);
        zZombie* zombie;
        foreach (zombie, this->scene->Zombies)
        {
            if ((qAbs(zombie->x() - this->x() + zombie->offset + 50) < 40) && ((this->raw) == (zombie->raw)))
            {
                if (this->alive)
                {
                    zAnim* mashedPotato = new zMashedPotato(scene);
                    mashedPotato->setGeometry(this->x() - 40, this->y(), 150, 100);
                    this->scene->Anims.append(mashedPotato);
                    QSound::play(":/Sounds/rc/Potato.wav");
                }
                this->alive = false;
                zombie->hit(1200);
            }
        }
    }
}

zPotatoMine::~zPotatoMine()
{
    delete this->anim;
    delete this->anim_1;
}



zFireTree::zFireTree(QWidget *parent) : zPlant(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->strength = 300;
}

void zFireTree::act()
{
    int i = 0;
    while (i < scene->FlyingObjects.count())
    {
        zFlyingObject* obj = scene->FlyingObjects[i];
        if (obj->canFire && (obj->raw == this->raw) && (qAbs(this->x() - obj->x() - 10) < 20))
        {
            zFirePea* firepea = new zFirePea(scene);
            firepea->setGeometry(obj->x(), obj->y(), 80, 40);
            firepea->raw = obj->raw;
            scene->FlyingObjects.append(firepea);
            delete obj;
            scene->FlyingObjects.removeAt(i);
        }
        else
        {
            i++;
        }
    }
}

zFireTree::~zFireTree()
{
    delete this->anim;
}



zCherryBomb::zCherryBomb(QWidget *parent) : zPlant(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->strength = 2000;
    this->TimerBoom = 12;
}

void zCherryBomb::act()
{
    if (this->TimerBoom > 0)
    {
        this->TimerBoom --;
    }
    else
    {
        zZombie* zombie;
        foreach (zombie, this->scene->Zombies)
        {
            if ((qAbs(zombie->x() - this->x() + zombie->offset + 50) < 140) && (qAbs(this->raw - zombie->raw) <= 1))
            {
                zombie->hit(1200);
            }
        }
        zAnim* boom = new zBoom(scene);
        boom->setGeometry(this->x() - 60, this->y() - 50, 200, 150);
        scene->Anims.append(boom);
        QSound::play(":/Sounds/rc/Boom.wav");
        this->alive = false;
    }
}

zCherryBomb::~zCherryBomb()
{
    delete this->anim;
}



zIcePeaShooter::zIcePeaShooter(QWidget *parent) : zPlant(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->TimerShoot_max = 50;
    this->TimerShoot = this->TimerShoot_max;
    this->strength = 200;
}

void zIcePeaShooter::act()
{
    if (this->TimerShoot <= 0)
    {
        if (!(scene->hasEnemy[this->raw]))
        {
            this->TimerShoot = qrand() % 20;// not to shoot too many peas in a single timer event
            return;
        }
        this->TimerShoot = this->TimerShoot_max;
        zIcePea* pea = new zIcePea(scene);
        pea->setGeometry(this->x() + 20, this->y() + 15 - (qrand() % 5), 80, 40);
        pea->raw = this->raw;
        scene->FlyingObjects.append(pea);
        QSound::play(":/Sounds/rc/PeaHit.wav");
    }
    else
    {
        this->TimerShoot --;
    }
}

zIcePeaShooter::~zIcePeaShooter()
{
    delete this->anim;
}



zMushroom::zMushroom(QWidget *parent) : zPlant(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->TimerShoot_max = 50;
    this->TimerShoot = this->TimerShoot_max;
    this->strength = 100;
}

void zMushroom::act()
{
    if (this->TimerShoot <= 0)
    {
        if (!(scene->hasEnemy[this->raw]))
        {
            this->TimerShoot = qrand() % 20;// not to shoot too many peas in a single timer event
            return;
        }
        this->TimerShoot = this->TimerShoot_max;
        zMush* mush = new zMush(scene);
        mush->setGeometry(this->x() + 20, this->y()+ 55 - (qrand() % 5), 80, 40);
        mush->raw = this->raw;
        scene->FlyingObjects.append(mush);
        QSound::play(":/Sounds/rc/Mush.wav");
    }
    else
    {
        this->TimerShoot --;
    }
}

zMushroom::~zMushroom()
{
    delete this->anim;
}
