
#include <iostream>
#include <QBrush>
#include <QPen>

#include "guiblock.h"

//#define sklad

#ifndef sklad
GuiBlock::GuiBlock(QPointF pos, QGraphicsItem *g):
  QGraphicsRectItem(g)
{
  QRectF rectangle/*(x, y, mwidth, mheight);*/ = QRectF(pos.x(),pos.y(),mwidth,mheight);
  QBrush brush = QBrush(Qt::darkGray, Qt::SolidPattern);
  QPen pen = QPen(brush, 5);

  //resize(mwidth, mheight);
  //move(x, y);
  //repaint();

  setRect(rectangle);
  setBrush(brush);
  setPen(pen);
}


QRectF GuiBlock::boundingRect() const { return rect(); }

void GuiBlock::paint(QPainter *p, const QStyleOptionGraphicsItem *s, QWidget *w)
{
  QGraphicsRectItem::paint(p,s,w);
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
