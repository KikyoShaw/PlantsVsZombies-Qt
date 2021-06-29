#include "zScene.h"
#include<QFile>
#include<QTextStream>
zScene::zScene(QWidget* parent) : zObject(parent)
{
    this->setMouseTracking(true);
    this->grabKeyboard();              //limit keyboard input
}

zScene::~zScene()
{
    while (!Zombies.empty())
    {
        delete Zombies[0];                 //delete QList
        Zombies.removeAt(0);
    }
    while (!Plants.empty())
    {
        delete Plants[0];
        Plants.removeAt(0);
    }
    while (!FlyingObjects.empty())
    {
        delete FlyingObjects[0];
        FlyingObjects.removeAt(0);
    }
    while (!Anims.empty())
    {
        delete Anims[0];
        Anims.removeAt(0);
    }
    while (!Bonuses.empty())
    {
        delete Bonuses[0];
        Bonuses.removeAt(0);
    }
    while (!Cards.empty())
    {
        delete Cards[0];
        Cards.removeAt(0);
    }
    if (!(this->SunFront == nullptr)) delete this->SunFront;
    if (!(this->SunBack == nullptr)) delete this->SunBack;
    if (!(this->sunback == nullptr))delete this->sunback;
    if (!(this->timer == nullptr))delete this->timer;}

QPoint zScene::getCell()
{
    if (this->rect.contains(this->m))
    {
        return QPoint((this->m.x() - this->rect.left()) / this->cellSize.x(),
                      (this->m.y() - this->rect.top()) / this->cellSize.y());
    }
    else
    {
        return QPoint(-1, -1);
    }
}

void zScene::removeDeath()
{
    int p = 0;
    while (p < Plants.count())
    {
        if (!(Plants[p]->alive))
        {
            delete (Plants[p]);
            Plants.removeAt(p);
        }
        else
        {
            p++;
        }
    }
    for (int i = 0; i < 6; i++)
    {
        this->hasEnemy[i] = false;
    }
    p = 0;
    while (p < Zombies.count())
    {
        if (!(Zombies[p]->alive))
        {
            delete (Zombies[p]);
            Zombies.removeAt(p);
        }
        else
        {
            this->hasEnemy[Zombies[p]->raw] = true;
            p++;
        }
    }
    p = 0;
    while (p < FlyingObjects.count())
    {
        if (!(FlyingObjects[p]->alive))
        {
            delete (FlyingObjects[p]);
            FlyingObjects.removeAt(p);
        }
        else
        {
            p++;
        }
    }
    p = 0;
    while (p < Anims.count())
    {
        if (!(Anims[p]->alive))
        {
            delete (Anims[p]);
            Anims.removeAt(p);
        }
        else
        {
            p++;
        }
    }
    p = 0;
    while (p < Bonuses.count())
    {
        if (!(Bonuses[p]->alive))
        {
            delete (Bonuses[p]);
            Bonuses.removeAt(p);
        }
        else
        {
            p++;
        }
    }
}

void zScene::act()
{
    zObject* i;
    foreach(i, Zombies)
    {
        i->act();
    }
    foreach(i, Plants)
    {
        i->act();
    }
    foreach(i, FlyingObjects)
    {
        i->act();
    }
    foreach(i, Anims)
    {
        i->act();
    }
    foreach(i, Bonuses)
    {
        i->act();
    }
    foreach(i, Cards)
    {
        i->act();
    }
}

void zScene::createZombie()
{
    if (this->threat < 9001)
    {
        this->threat ++;
    }
    if (this->Zombies.count() < (this->threat / 600))
    {
        if (this->threat < 5000)
        {
            this->putZombie(qrand() % 5, 0);
        }
        else
        {
            this->putZombie(qrand() % 5, qrand() % 7);
        }
    }
}

void zScene::judge()
{
    if (this->TimerLose > 1)
    {
        this->TimerLose --;
    }
    else
    {
        if (this->TimerLose == 1)
        {
            emit toTitle();
        }
        else
        {
            zZombie* zombie;
            foreach(zombie, Zombies)
            {
                if (zombie->x() + zombie->offset < 130)
                {
                    this->currentCard = nullptr;
                    while (!Cards.empty())
                    {
                        delete Cards[0];
                        Cards.removeAt(0);
                    }
                    this->SunBack->hide();
                    this->SunFront->hide();
                    this->move(0, 0);
                    QSound::play(":/Sounds/rc/Lose.wav");
                    this->TimerLose = 100;
                    return;
                }
            }
        }
    }
}

void zScene::uiSetup()
{

}

void zScene::putPlant(QPoint t_cell)
{
    zPlant* plant;
    switch (this->currentCard->plantIndex)
    {
    case 0:
        for (int i = 0; i < Plants.count(); i++)
        {
            if ((Plants[i]->raw == t_cell.y()) && (Plants[i]->column == t_cell.x()))
            {
                delete Plants[i];
                Plants.removeAt(i);
                this->currentCard->move(this->currentPos);
                this->currentCard = nullptr;
                return;
            }
        }
        this->currentCard = nullptr;
        return;
        break;
    case 1:
        plant = new zSunFlower(this);
        break;
    case 2:
        plant = new zPeaShooter(this);
        break;
    case 3:
        plant = new zWallNut(this);
        break;
    case 4:
        plant = new zRepeater(this);
        break;
    case 5:
        plant = new zPotatoMine(this);
        break;
    case 6:
        plant = new zFireTree(this);
        break;
    case 7:
        plant = new zCherryBomb(this);
        break;
    case 8:
        plant = new zIcePeaShooter(this);
        break;
    case 9:
        plant = new zMushroom(this);
        break;
    }
    plant->setGeometry(this->rect.x() + 10 + this->cellSize.x() * t_cell.x(), this->rect.y() - 15 + this->cellSize.y() * t_cell.y(), 120, 100);
    plant->raw = t_cell.y();
    plant->column = t_cell.x();
    this->Plants.append(plant);
    this->sunPoint -= this->currentCard->sunPoint;
    this->currentCard->frame = this->currentCard->frame_max;
    this->currentCard = nullptr;
}

void zScene::putZombie(int raw, int type)
{
    zZombie* zombie;
    switch(type)
    {
    case 0:
        zombie = new zCommonZombie(this, 0);
        break;
    case 1:
        zombie = new zCommonZombie(this, 1);
        break;
    case 2:
        zombie = new zCommonZombie(this, 2);
        break;
    case 3:
        zombie = new zCommonZombie(this, 3);
        break;
    case 4:
        zombie = new zCommonZombie(this, 4);
        break;
    case 5:
        zombie = new zPoleZombie(this);
        break;
    case 6:
        zombie = new zNewsZombie(this);
        break;
    }
    zombie->raw = raw;
    zombie->setGeometry(950, zombie->raw * 100 - 25 + qrand() % 5, 340, 200);
    this->Zombies.append(zombie);
}

void zScene::mouseMoveEvent(QMouseEvent* event)
{
    m = event->pos();
    if (this->currentCard != nullptr)
    {
        this->currentCard->move(m + QPoint(-40, 1));
    }
}

void zScene::mousePressEvent(QMouseEvent *event)
{
    QPoint m_cell = this->getCell();
    if (event->button() == Qt::LeftButton)
    {
        if ((m_cell.x() > -1) && (this->currentCard != nullptr))
        {
            for (int i = 0; i < Plants.count(); i++)
            {
                if ((Plants[i]->raw == m_cell.y()) && (Plants[i]->column == m_cell.x()) && this->currentCard->plantIndex > 0)
                {
                    QSound::play(":/Sounds/rc/NotEnoughSun.wav");
                    return;
                }
            }
            this->currentCard->move(this->currentPos);
            this->putPlant(m_cell);
            QSound::play(":/Sounds/rc/Place.wav");
        }
    }
    else
    {
        if (this->currentCard != nullptr)
        {
            this->currentCard->move(this->currentPos);
        }
        this->currentCard = nullptr;
    }
}



zLawnScene::zLawnScene(QWidget* parent) : zScene(parent)
{
    this->setGeometry(-120, 0, 1400, 600);
    this->cellSize = QPoint(81, 100);
    this->rect = QRect(250, 85, 729, 500);
    this->setMovie(this->background);
    this->background->start();
    this->show();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer->start(20);
    this->uiSetup();
}

zLawnScene::~zLawnScene()
{
    delete this->background;
}

void zLawnScene::uiSetup()
{
    SunBack->setGeometry(120, 0, 123, 34);
    sunback->start();
    SunBack->show();
    SunBack->setMovie(sunback);
    SunFront->setGeometry(160, 0, 65, 30);
    SunFront->setFont(QFont("Calibri", 16));
    SunFront->setText("50");
    SunFront->setAlignment(Qt::AlignHCenter);
    SunFront->show();
    SunFront->raise();
    exit->setGeometry(950, 0, 60, 60);
    exit->setFlat(true);
    exit->setIcon(QIcon(":/Interface/rc/Leave.png"));
    exit->setIconSize(QSize(60,60));
    exit->setStyleSheet("background: transparent");
    exit->setCursor(Qt::PointingHandCursor);
    connect(exit, SIGNAL(clicked()), this, SLOT(leave()));
    exit->show();
    exit->raise();
    zCard *card = new zSunFlowerCard(this);
    card->setIndex(0);
    Cards.append(card);
    zCard *card_2 = new zPeaShooterCard(this);
    card_2->setIndex(1);
    Cards.append(card_2);
    zCard *card_3 = new zWallNutCard(this);
    card_3->setIndex(2);
    Cards.append(card_3);
    zCard *card_4 = new zRepeaterCard(this);
    card_4->setIndex(4);
    Cards.append(card_4);
    zCard *card_5 = new zPotatoMineCard(this);
    card_5->setIndex(5);
    Cards.append(card_5);
    zCard *card_6 = new zFireTreeCard(this);
    card_6->setIndex(6);
    Cards.append(card_6);
    zCard *card_7 = new zCherryBombCard(this);
    card_7->setIndex(7);
    Cards.append(card_7);
    zCard *card_8 = new zIcePeaShooterCard(this);
    card_8->setIndex(3);
    Cards.append(card_8);
    zCard *shovel = new zShovel(this);
    Cards.append(shovel);
}

void zLawnScene::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_1:
        this->putZombie(qrand() % 5, 0);
        break;
    case Qt::Key_2:
        this->putZombie(qrand() % 5, 1);
        break;
    case Qt::Key_3:
        this->putZombie(qrand() % 5, 2);
        break;
    case Qt::Key_4:
        this->putZombie(qrand() % 5, 3);
        break;
    case Qt::Key_5:
        this->putZombie(qrand() % 5, 4);
        break;
    case Qt::Key_6:
        this->putZombie(qrand() % 5, 5);
        break;
    case Qt::Key_7:
        this->putZombie(qrand() % 5, 6);
        break;
    case Qt::Key_8:
        this->sunPoint += 100;
        break;
    case Qt::Key_9:
        this->threat = 6001;
        break;
    case Qt::Key_Escape:
        emit toTitle();
        break;
    }
}

void zLawnScene::onTimer()
{
    this->removeDeath();
    this->act();
    this->SunFront->setText(QString::number(this->sunPoint));
    this->createZombie();
    if (qrand() % 521 < 1)
    {
        zBonus* sun = new zSunFall(this);
        Bonuses.append(sun);
    }
    this->exit->raise();
    this->judge();
}

void zLawnScene::leave()
{
    emit toTitle();
}




zDarkScene::zDarkScene(QWidget* parent) : zScene(parent)
{
    this->setGeometry(-120, 0, 1400, 600);
    this->cellSize = QPoint(81, 100);
    this->rect = QRect(250, 85, 729, 500);
    this->setMovie(this->background);
    this->background->start();
    this->show();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer->start(20);
    this->uiSetup();
}

zDarkScene::~zDarkScene()
{
    delete this->background;
}

void zDarkScene::uiSetup()
{
    SunBack->setGeometry(120, 0, 123, 34);
    sunback->start();
    SunBack->show();
    SunBack->setMovie(sunback);
    SunFront->setGeometry(160, 0, 65, 30);
    SunFront->setFont(QFont("Calibri", 16));
    SunFront->setText("50");
    SunFront->setAlignment(Qt::AlignHCenter);
    SunFront->show();
    SunFront->raise();
    exit->setGeometry(950, 0, 60, 60);
    exit->setFlat(true);
    exit->setIcon(QIcon(":/Interface/rc/Leave.png"));
    exit->setIconSize(QSize(60,60));
    exit->setStyleSheet("background: transparent");
    exit->setCursor(Qt::PointingHandCursor);
    connect(exit, SIGNAL(clicked()), this, SLOT(leave()));
    exit->show();
    exit->raise();
    zCard *card = new zSunFlowerCard(this);
    card->setIndex(1);
    Cards.append(card);
    zCard *card_2 = new zPeaShooterCard(this);
    card_2->setIndex(2);
    Cards.append(card_2);
    zCard *card_3 = new zWallNutCard(this);
    card_3->setIndex(3);
    Cards.append(card_3);
    zCard *card_4 = new zRepeaterCard(this);
    card_4->setIndex(5);
    Cards.append(card_4);
    zCard *card_5 = new zPotatoMineCard(this);
    card_5->setIndex(6);
    Cards.append(card_5);
    zCard *card_6 = new zFireTreeCard(this);
    card_6->setIndex(7);
    Cards.append(card_6);
    zCard *card_7 = new zCherryBombCard(this);
    card_7->setIndex(8);
    Cards.append(card_7);
    zCard *card_8 = new zIcePeaShooterCard(this);
    card_8->setIndex(4);
    Cards.append(card_8);
    zCard *card_9 = new zMushroomCard(this);
    card_9->setIndex(0);
    Cards.append(card_9);
    zCard *shovel = new zShovel(this);
    Cards.append(shovel);
    //this->music = new QSound(":/music/rc/Scene2.wav");
    //this->music->setLoops(-1);
    //this->music->play();
}

void zDarkScene::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_1:
        this->putZombie(qrand() % 5, 0);
        break;
    case Qt::Key_2:
        this->putZombie(qrand() % 5, 1);
        break;
    case Qt::Key_3:
        this->putZombie(qrand() % 5, 2);
        break;
    case Qt::Key_4:
        this->putZombie(qrand() % 5, 3);
        break;
    case Qt::Key_5:
        this->putZombie(qrand() % 5, 4);
        break;
    case Qt::Key_6:
        this->putZombie(qrand() % 5, 5);
        break;
    case Qt::Key_7:
        this->putZombie(qrand() % 5, 6);
        break;
    case Qt::Key_8:
        this->sunPoint += 100;
        break;
    case Qt::Key_9:
        this->threat = 6001;
        break;
    case Qt::Key_Escape:
        emit toTitle();
        break;
    }
}

void zDarkScene::onTimer()
{
    this->removeDeath();
    this->act();
    this->createZombie();
    this->exit->raise();
    this->SunFront->setText(QString::number(this->sunPoint));
    this->judge();
}

void zDarkScene::leave()
{
    emit toTitle();
}



zStartScene::zStartScene(QWidget* parent) : zScene(parent)
{
    this->setGeometry(0, 0, 800, 600);
    this->setMovie(this->background);
    this->background->start();
    this->show();
    btn1->setStyleSheet("QLabel{border: 5px solid #000000;} QLabel:hover{border:10px solid #EE0000;}");
    btn2->setStyleSheet("QLabel{border: 5px solid #000000;} QLabel:hover{border:10px solid #EE0000;}");
    btn1->setMovie(lawn);
    lawn->start();
    btn2->setMovie(dark);
    dark->start();
    btn1->setGeometry(120, 205, 180, 180);
    btn2->setGeometry(500, 205, 180, 180);
    btn1->show();
    btn2->show();
    title->setText("Select a Scene");
    title->setGeometry(290, 0, 240, 100);
    title->setFont(QFont("Consolas", 18));
    title->show();

    //文件操作 设置从文本读取用户名和时间
    QFile file(":/user.txt");      //文件操作 读取文件中的用户名
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QStringList string_list;
    QString line = in.readLine();
    string_list=line.split(" ");   //分割文本 用元素初始化对象

    QString user_name=string_list[0];
    QString best_time=string_list[1];
    QString str1="User: "+user_name;
    QString str2="BestTime: "+best_time;
    UserName->setGeometry(40, 430, 300, 100);
    BestTime->setGeometry(40,460,300,100);
    UserName->setText(str1);
    BestTime->setText(str2);
    UserName->setFont(QFont("Consolas", 14));
    BestTime->setFont(QFont("Consolas", 14));
    UserName->show();
    BestTime->show();
    file.close();

}

zStartScene::~zStartScene()
{
    delete this->background;
    delete this->lawn;
    delete this->dark;
    delete this->btn1;
    delete this->btn2;
    delete this->title;
}


void zStartScene::mousePressEvent(QMouseEvent *event)
{
    if (QRect(120, 205, 180, 180).contains(event->pos()))
    {
        emit toLawn();
    }
    if (QRect(500, 205, 180, 180).contains(event->pos()))
    {
        emit toDarkLawn();
    }
}



zStartScreen::zStartScreen(QWidget* parent) : zScene(parent)
{
    this->setGeometry(0, 0, 800, 600);
    this->setMovie(this->background);
    this->background->start();
    this->show();
    this->front->setGeometry(0, 0, 800, 600);
    this->front->show();
    this->front->setStyleSheet("background: rgba(0,0,0,1)");
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer->start(20);
}

zStartScreen::~zStartScreen()
{
    delete this->background;
    delete this->front;
}

void zStartScreen::onTimer()
{
    if (frame > 0)
    {
        frame --;
        if (frame > 50)
        {
            this->front->setStyleSheet("background: rgba(0,0,0," + QString::number((frame - 50) / 50.0) +")");
        }
        if (frame < 30)
        {
            this->front->setStyleSheet("background: rgba(0,0,0," + QString::number((30 - frame) / 30.0) +")");
        }
    }
    else
    {
        emit toTitle();
    }
}
