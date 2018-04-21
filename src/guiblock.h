#ifndef GUIBLOCK_H
#define GUIBLOCK_H

#include <QWidget>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QPointF>
#include <QRectF>

class GuiBlock: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
  public:
    GuiBlock(QPointF pos, QGraphicsItem* g = 0);

    //QRectF boundingRect() const override;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;

    void mousePressEvent(QGraphicsSceneMouseEvent*);

    void contains(QPointF);

    QGraphicsSceneMouseEvent * getMouseEvent() { return MPEvent; }

  signals:
         /**
         * @brief   Signal to the PlayGround, mouse click.
         */
        void sigBlockClick();

  private:
    QRectF mrectangle;/*
    QBrush brush;
    QPen pen;*/
    double mwidth = 30;
    double mheight = 30;

    QGraphicsSceneMouseEvent * MPEvent = nullptr;
};

#endif // GUIBLOCK_H
