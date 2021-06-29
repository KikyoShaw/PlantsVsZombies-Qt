#include "maindialog.h"
#include<QFile>
#include<QTextStream>
mainDialog::mainDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowIcon(QIcon(QStringLiteral(":/Interface/rc/mainlogo.png")));
    this->setMouseTracking(true);                //track mouse when mouse isn`t pressed
    this->setFixedSize(800, 600);
    scene = new zStartScreen(this);
    connect(this->scene, SIGNAL(toTitle()), this, SLOT(back()));



}

mainDialog::~mainDialog()
{
    delete ui;
	exit(0);
}

void mainDialog::startLawn()
{
    this->setFixedSize(900, 600);
    delete scene;                            //remeber to delete !!!
    scene = new zLawnScene(this);
    connect(this->scene, SIGNAL(toTitle()), this, SLOT(back()));
}

void mainDialog::startDark()
{
    this->setFixedSize(900, 600);
    delete scene;
    scene = new zDarkScene(this);
    connect(this->scene, SIGNAL(toTitle()), this, SLOT(back()));
}

void mainDialog::back()
{
    this->setFixedSize(800, 600);
    delete scene;
    scene = new zStartScene(this);
    connect(this->scene, SIGNAL(toLawn()), this, SLOT(startLawn()));
    connect(this->scene, SIGNAL(toDarkLawn()), this, SLOT(startDark()));
}
