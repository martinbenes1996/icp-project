#ifndef GUIBLOCK_H
#define GUIBLOCK_H

#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QPointF>
#include <QRectF>

class GuiBlock: public QGraphicsRectItem
{
  public:
    GuiBlock(QPointF, QGraphicsItem* g = 0);

    QRectF boundingRect() const override;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;

  private:
    double mwidth = 10;
    double mheight = 10;
};

#endif // GUIBLOCK_H
