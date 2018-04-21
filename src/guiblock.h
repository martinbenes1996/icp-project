#ifndef GUIBLOCK_H
#define GUIBLOCK_H

#include <iostream>

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

    // QRectF boundingRect() const override;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;

    void mousePressEvent(QGraphicsSceneMouseEvent*);

    void contains(QPointF);

    QGraphicsSceneMouseEvent * getMouseEvent() { return MPEvent; }

    // methods for different blocks
    void getPoint_2I1O(QPointF *point);
    // ----------------------------

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

    // different blocks variables - I/O
    bool input1 = false;
    bool input2 = false;
    bool output1 = false;
    bool output2 = false;
};

#endif // GUIBLOCK_H
