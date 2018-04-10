#ifndef GUIBLOCK_H
#define GUIBLOCK_H

#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QPointF>

class GuiBlock: public QObject, public QRectF
{
  Q_OBJECT
  public:
    GuiBlock(QPointF);

    QGraphicsRectItem *getGRect() { return mgraphic; }
  private:
    double mwidth = 10;
    double mheight = 10;

    QGraphicsRectItem * mgraphic = nullptr;
};

#endif // GUIBLOCK_H
