
#include <QBrush>
#include <QPen>

#include "guiblock.h"

GuiBlock::GuiBlock(QPointF pos, QGraphicsItem *g):
  QGraphicsRectItem(g)
{
  QRectF r = QRectF(pos.x(),pos.y(),mwidth,mheight);
  QBrush b = QBrush(Qt::darkGray, Qt::SolidPattern);
  QPen p = QPen(b, 5);

  setRect(r);
  setBrush(b);
  setPen(p);
}

QRectF GuiBlock::boundingRect() const { return rect(); }
  
void GuiBlock::paint(QPainter *p, const QStyleOptionGraphicsItem *s, QWidget *w)
{
  QGraphicsRectItem::paint(p,s,w);
}
  