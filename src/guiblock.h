#ifndef GUIBLOCK_H
#define GUIBLOCK_H

#include <QWidget>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QPointF>
#include <QRectF>

class GuiBlock: public QGraphicsRectItem
{
  public:
    GuiBlock(QPointF pos, QGraphicsItem* g = 0);

    QRectF boundingRect() const override;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;

    void contains(QPointF);

  private:/*
    QRect rectangle;
    QBrush brush;
    QPen pen;*/
    double mwidth = 30;
    double mheight = 30;
};

#endif // GUIBLOCK_H
