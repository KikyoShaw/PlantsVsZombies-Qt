#include "zCard.h"

zCard::zCard(QWidget* parent) : zObject(parent)
{
    this->setCursor(Qt::PointingHandCursor);
    back = new QWidget(this);
    back->setStyleSheet("background-color: rgba(0, 0, 0, 50%);");
    back->show();
    back->raise();
    front = new QWidget(this);
    front->setStyleSheet("background-color: rgba(0, 0, 0, 50%);");
    front->show();
    front->raise();
    frontText = new QLabel(this);
    frontText->setText("50");
    frontText->setGeometry(60, 33, 40, 20);
    frontText->setAlignment(Qt::AlignHCenter);
    frontText->setFont(QFont("Calibri", 11));
    frontText->show();
    frontText->raise();
    this->show();
    this->raise();
}

void zCard::act()
{
    if (this->frame > 0)
    {
        this->frame --;
    }
    this->transFront();
    this->raise();
}

void zCard::setIndex(int index)
{
    this->setGeometry(125, 40 + 60 * index, 100, 60);
}

void zCard::transFront()
{
    front->setGeometry(0, 6, 100, 54 * this->frame / this->frame_max);
    if (scene->sunPoint >= this->sunPoint)
    {
        back->setGeometry(0, 0, 0, 0);
    }
    else
    {
        back->setGeometry(0, 6, 100, 54);
    }
}

void zCard::mousePressEvent(QMouseEvent* event)
{
    if (scene->currentCard != nullptr)
    {
        scene->currentCard->move(scene->currentPos);
    }
    if (event->button() == Qt::LeftButton)
    {
        if (this->front->height() > 0)
        {
            QSound::play(":/Sounds/rc/NotEnoughSun.wav");
            scene->currentCard = nullptr;
            return;
        }
        if (this->scene->sunPoint < this->sunPoint)
        {
            QSound::play(":/Sounds/rc/NotEnoughSun.wav");
            scene->currentCard = nullptr;
            return;
        }
        QSound::play(":/Sounds/rc/Place.wav");
        scene->currentPos = this->pos();
        scene->currentCard = this;
    }
    else
    {
        scene->currentCard = nullptr;
    }
}

zCard::~zCard()
{
    delete (this->back);
    delete (this->front);
    delete (this->frontText);
}

zSunFlowerCard::zSunFlowerCard(QWidget* parent) : zCard(parent)
{
    this->setMovie(anim);
    anim->start();
    this->frontText->setText("50");
    this->frame_max = 100;
    this->frame = 100;
    this->plantIndex = 1;
    this->sunPoint = 50;
}

zSunFlowerCard::~zSunFlowerCard()
{
    delete this->anim;
}

zPeaShooterCard::zPeaShooterCard(QWidget* parent) : zCard(parent)
{
    this->setMovie(anim);
    anim->start();
    this->frontText->setText("100");
    this->frame_max = 100;
    this->frame = 100;
    this->plantIndex = 2;
    this->sunPoint = 100;
}

zPeaShooterCard::~zPeaShooterCard()
{
    delete this->anim;
}

zWallNutCard::zWallNutCard(QWidget* parent) : zCard(parent)
{
    this->setMovie(anim);
    anim->start();
    this->frontText->setText("50");
    this->frame_max = 500;
    this->frame = 500;
    this->plantIndex = 3;
    this->sunPoint = 50;
}

zWallNutCard::~zWallNutCard()
{
    delete this->anim;
}

zRepeaterCard::zRepeaterCard(QWidget* parent) : zCard(parent)
{
    this->setMovie(anim);
    anim->start();
    this->frontText->setText("200");
    this->frame_max = 100;
    this->frame = 100;
    this->plantIndex = 4;
    this->sunPoint = 200;
}

zRepeaterCard::~zRepeaterCard()
{
    delete this->anim;
}

zPotatoMineCard::zPotatoMineCard(QWidget* parent) : zCard(parent)
{
    this->setMovie(anim);
    anim->start();
    this->frontText->setText("25");
    this->frame_max = 500;
    this->frame = 500;
    this->plantIndex = 5;
    this->sunPoint = 25;
}

zPotatoMineCard::~zPotatoMineCard()
{
    delete this->anim;
}

zFireTreeCard::zFireTreeCard(QWidget* parent) : zCard(parent)
{
    this->setMovie(anim);
    anim->start();
    this->frontText->setText("175");
    this->frame_max = 300;
    this->frame = 300;
    this->plantIndex = 6;
    this->sunPoint = 175;
}

zFireTreeCard::~zFireTreeCard()
{
    delete this->anim;
}

zCherryBombCard::zCherryBombCard(QWidget* parent) : zCard(parent)
{
    this->setMovie(anim);
    anim->start();
    this->frontText->setText("150");
    this->frame_max = 500;
    this->frame = 500;
    this->plantIndex = 7;
    this->sunPoint = 150;
}

zCherryBombCard::~zCherryBombCard()
{
    delete this->anim;
}

zIcePeaShooterCard::zIcePeaShooterCard(QWidget* parent) : zCard(parent)
{
    this->setMovie(anim);
    anim->start();
    this->frontText->setText("175");
    this->frame_max = 100;
    this->frame = 100;
    this->plantIndex = 8;
    this->sunPoint = 175;
}

zIcePeaShooterCard::~zIcePeaShooterCard()
{
    delete this->anim;
}

zMushroomCard::zMushroomCard(QWidget* parent) : zCard(parent)
{
    this->setMovie(anim);
    anim->start();
    this->frontText->setText("0");
    this->frame_max = 300;
    this->frame = 300;
    this->plantIndex = 9;
    this->sunPoint = 0;
}

zMushroomCard::~zMushroomCard()
{
    delete this->anim;
}

zShovel::zShovel(QWidget* parent) : zCard(parent)
{
    this->setMovie(anim);
    this->setGeometry(250, 5, 76, 34);
    anim->start();
    this->frontText->setText("");
    this->frame_max = 1;
    this->frame = 0;
    this->plantIndex = 0;
    this->sunPoint = 0;
}

zShovel::~zShovel()
{
    delete this->anim;
}
