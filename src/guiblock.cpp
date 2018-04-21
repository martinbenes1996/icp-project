
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
  QRectF rectangle = QRectF(pos.x()-mwidth/2,pos.y()-mheight/2,mwidth,mheight);
  QBrush brush = QBrush(Qt::darkGray, Qt::SolidPattern);
  QPen pen = QPen(brush, 5);

  setRect(rectangle);
  setBrush(brush);
  setPen(pen);
  setAcceptDrops(true);
}

// hopefully this will do it
QRectF GuiBlock::boundingRect() const { return rect(rectangle.topLeft().x(), rectangle.topLeft().y(), mwidth, mheight); }

void GuiBlock::paint(QPainter *p, const QStyleOptionGraphicsItem *s, QWidget *w)
{
  QGraphicsRectItem::paint(p,s,w);

}

void GuiBlock::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    //std::cerr << "Block clicked!\n";

    if(event->button() == Qt::LeftButton)
    {
        std::cout << "GuiBlock: sends signal left click\n";
        emit sigBlockLeftClick(event);
    }
    else if(event->button() == Qt::RightButton)
    {
        std::cout << "GuiBlock: sends signal right click\n";
        emit sigBlockRightClick(event);
    }
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
