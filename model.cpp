
#include "model.h"

#include <QDebug>
#include <QtMath>

//! [0]
CarModel::CarModel(QObject *parent) :
    QObject(parent), speed(0.0f), direction(0.0f)
{

}

void CarModel::update(const int elapsed) {
    qDebug() << "model update";

    if(speed>0.0f)
        speed-=1.0f;
    else if(speed<0.0f)
        speed+=1.0f;

    qfloat16 stepX=(speed*elapsed/10000)*qCos(qDegreesToRadians(direction));
    qfloat16 stepY=(speed*elapsed/10000)*qSin(qDegreesToRadians(direction));
    position.first+=stepX;
    position.second+=stepY;


}

void CarModel::accel(const bool more) {
    qfloat16 step=10.0f;
    if(more)
        speed+=step;
    else
        speed-=step;

    if(speed>100.0f)
        speed=100.0f;
    else if(speed<-100.0f)
        speed=-100.0f;
}

void CarModel::rotate(const bool left) {
    qfloat16 step=10.0f;
    if(!left)
        direction+=step;
    else
        direction-=step;

    if(direction>360.0f)
        direction=0.0f;
}

void CarModel::reset(const qfloat16 x, const qfloat16 y) {
    position.first=x;
    position.second=y;
    direction=0.0f;
    speed=0.0f;
};

const qfloat16 CarModel::getX() const {
    return position.first;
}

const qfloat16 CarModel::getY() const {
    return position.second;
}

const qfloat16 CarModel::getD() const {
    return direction;
}
