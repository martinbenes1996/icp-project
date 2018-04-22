
#include <iostream>
#include <QBrush>
#include <QPen>

#include "guiblock.h"
#include "window.h"

//#define sklad

#ifndef sklad
GuiBlock::GuiBlock(QPointF pos, QGraphicsItem *g):
  QGraphicsRectItem(g)
{
  mrectangle = QRectF(pos.x()-mwidth/2,pos.y()-mheight/2,mwidth,mheight);
  QBrush brush = QBrush(Qt::darkGray, Qt::SolidPattern);
  QPen pen = QPen(brush, 1);

  setRect(mrectangle);
  setBrush(brush);
  setPen(pen);
  setAcceptDrops(true);
  setAcceptHoverEvents(true);
}

//QRectF GuiBlock::boundingRect() const { return rect(mrectangle.topLeft().x(), mrectangle.topLeft().y(), mwidth, mheight); }

void GuiBlock::paint(QPainter *p, const QStyleOptionGraphicsItem *s, QWidget *w)
{
  QGraphicsRectItem::paint(p,s,w);

}

void GuiBlock::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    //std::cerr << "...!\n";
    MPEvent = event;
    emit sigBlockClick();
}

// block methods ---------------------------------------------
void GuiBlock::getPoint_2I1O(QPointF *point)
{
    std::cout << "getPoint_2I1O: im here!\n";
    QPointF itemPoint = mrectangle.center();
    QRectF tempRect1 = QRectF(itemPoint.x()-mwidth/2, itemPoint.y()-mheight/2, mwidth/2.0, mheight/2.0);
    QRectF tempRect2 = QRectF(itemPoint.x(), itemPoint.y()-mheight/2, mwidth/2.0, mheight/2.0);
    QRectF tempRect3 = QRectF(itemPoint.x()-mwidth/2, itemPoint.y(), mwidth/2.0, mheight/2.0);
    QRectF tempRect4 = QRectF(itemPoint.x(), itemPoint.y(), mwidth/2.0, mheight/2.0);

    //std::cout << itemPoint.x() << itemPoint.y() << std::endl;
    if(tempRect1.contains(MPEvent->pos().x(), MPEvent->pos().y()))
    {
        point->setX(itemPoint.x() - mwidth/2);
        point->setY(itemPoint.y() - mheight/4);
        std::cout << "levy horni roh itemu!\n";
        return;
    }
    else if(tempRect2.contains(MPEvent->pos().x(), MPEvent->pos().y()))
    {
        point->setX(itemPoint.x() + mwidth/2);
        point->setY(itemPoint.y() - mheight/4);
        std::cout << "pravy horni roh itemu!\n";
        return;
    }
    else if(tempRect3.contains(MPEvent->pos().x(), MPEvent->pos().y()))
    {
        point->setX(itemPoint.x() - mwidth/2);
        point->setY(itemPoint.y() + mheight/4);
        std::cout << "levy dolni roh itemu!\n";
        return;
    }
    else if(tempRect4.contains(MPEvent->pos().x(), MPEvent->pos().y()))
    {
        point->setX(itemPoint.x() + mwidth/4);
        point->setY(itemPoint.y() + mheight/4);
        std::cout << "pravy dolni roh itemu!\n";
        return;
    }
}

void GuiBlock::hoverEnterEvent(QGraphicsSceneHoverEvent*)
{
    std::cerr << "enter\n";
    QBrush b = brush();
    b.setColor(Qt::gray);
    setBrush(b);
}
void GuiBlock::hoverLeaveEvent(QGraphicsSceneHoverEvent*)
{
    std::cerr << "leave\n";
    QBrush b = brush();
    b.setColor(Qt::darkGray);
    setBrush(b);
}

#endif

#ifdef sklad

GuiBlock::GuiBlock(int x, int y/*, QGraphicsItem *g*/)//:
  //QGraphicsRectItem(g)
{
  QRect rectangle(x, y, mwidth, mheight); /*= QRectF(pos.x(),pos.y(),mwidth,mheight);*/
  QBrush brush = QBrush(Qt::darkGray, Qt::SolidPattern);
  QPen pen = QPen(brush, 5);

  resize(mwidth, mheight);
  move(x, y);
  repaint();
/*
  setRect(r);
  setBrush(b);
  setPen(p);*/
}

void GuiBlock::paintEvent(/*QPaintEvent**/)
{
    QPainter painter(this);
std::cout << "kreslim\n";
    painter.setPen(pen);
    painter.drawRect(rectangle);
}
void GuiBlock::mousePressEvent(QMouseEvent *event)
{
    (void *)event;
    std::cout << "click on widget\n";
}

/*
QRectF GuiBlock::boundingRect() const { return rect(); }
*/
void GuiBlock::paint(/*QPainter *p, const QStyleOptionGraphicsItem *s, QWidget *w*/)
{
  //QGraphicsRectItem::paint(p,s,w);
    QPainter painter(this);
std::cout << "kreslim\n";
    painter.setPen(pen);
    painter.drawRect(rectangle);
}
#endif
