#include "zObject.h"

zObject::zObject(QWidget *parent) : QLabel(parent)
{
    this->setMouseTracking(true);
    this->scene = (zScene*)this->parent();
}
