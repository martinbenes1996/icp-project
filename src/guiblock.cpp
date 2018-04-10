
#include <QBrush>

#include "guiblock.h"

GuiBlock::GuiBlock(QPointF pos):
  QRectF(pos.x(), pos.y(), mwidth, mheight)
{
  setWidth(mwidth);
  setHeight(mheight);

  mgraphic = new QGraphicsRectItem(*this);

  QBrush b(Qt::darkGray, Qt::SolidPattern);
  mgraphic->setBrush(b);
}
