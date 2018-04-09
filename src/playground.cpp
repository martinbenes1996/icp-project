#include <iostream>

#include <QMouseEvent>
#include <QPainter>

#include "playground.h"

PlayGround::PlayGround(QWidget* parent): QWidget(parent)
{

}

void PlayGround::mouseMoveEvent(QMouseEvent *event)
{
    (void)event;
    std::cout << "PlayGround::mouseMoveEvent()\n";
}

void PlayGround::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton) { emit sigChoiceRejected(); }
    (void)event;
    std::cout << "PlayGround::mousePressEvent()\n";
}

void PlayGround::mouseReleaseEvent(QMouseEvent *event)
{
    QPointF pos = event->localPos();
    mpoints.push_back(pos);
    update();
    
    //(void)event;
    //std::cout << "PlayGround::mouseReleaseEvent()\n";
}

void PlayGround::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setPen(Qt::blue);
    p.setBrush(Qt::SolidPattern);
    for(auto& it: mpoints)
        p.drawEllipse(it, 5, 5);
}

void PlayGround::slotChoiceMode(bool choice) { mchoice = choice; }