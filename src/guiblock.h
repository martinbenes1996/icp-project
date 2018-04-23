#ifndef GUIBLOCK_H
#define GUIBLOCK_H

#include <iostream>

#include <QWidget>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QPointF>
#include <QRectF>
#include <QBrush>
#include <QPen>
#include <QLineF>

class GuiBlock: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
  public:
    GuiBlock(QPointF pos, int typeOfBlock, QGraphicsItem* g = 0);

    // QRectF boundingRect() const override;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;

    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void hoverEnterEvent(QGraphicsSceneHoverEvent*);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*);

    void contains(QPointF);

    QGraphicsSceneMouseEvent * getMouseEvent() { return MPEvent; }

    // methods for different blocks
    void getPointFromBlock(int *connector, bool *wireFree);
    QPointF getConnectorPoint(int connector);
    //QPointF getInput_2Point();
    //QPointF getOutput_1Point();
    //QPointF getOutput_2Point();
    void setConnectorAvailability(int connector, bool addWire);
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
    int type;

    QBrush blockBrush;
    QPen blockPen;

    bool input1 = false;
    bool input2 = false;
    bool output1 = false;
    bool output2 = false;
};



/* Wire is here for now */
class MyLine: public QLineF//, public QObject
{
    //Q_OBJECT

    using QLineF::QLineF;

    /*public:
        void mousePressEvent(QGraphicsSceneMouseEvent*);
    signals:*/
        /**
         * @brief   Signal to the PlayGround, mouse click.
         */
        //void sigWireClick();
    private:
        //QGraphicsSceneMouseEvent * MPEvent = nullptr;
};

class MyWire: public QObject
{
    Q_OBJECT
    public:
        MyWire(QPointF point1, QPointF point2);

        QLineF getLine() { return line; }
    private:
        QLineF line;
        // text <- depends on value from module (connect with signal)
};


#endif // GUIBLOCK_H
