#ifndef ZOBJECT_H
#define ZOBJECT_H

#include <QLabel>
#include <QMovie>
#include <QMouseEvent>

class zScene;

class zObject : public QLabel
{
    Q_OBJECT
public:
    explicit zObject(QWidget* parent = 0);
    bool alive = true;
    virtual void act()=0;
    int strength = 1;
    zScene* scene;
};

#endif // ZOBJECT_H
