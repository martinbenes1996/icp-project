#ifndef GUIBLOCK_H
#define GUIBLOCK_H

#include <iostream>
#include <string>

#include <QWidget>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
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
class MyLine: public QObject, public QGraphicsLineItem
{
    Q_OBJECT

    public:
        MyLine(QPointF s, QPointF f, QGraphicsItem* parent = 0):
            QGraphicsLineItem(s.x(), s.y(), f.x(), f.y(), parent) {}

        void mousePressEvent(QGraphicsSceneMouseEvent* event) 
        {
            if(event->button() == Qt::LeftButton) { emit sigForkWire(event->pos()); }
            else if(event->button() == Qt::RightButton) { emit sigDeleteWire(); }
        }
    signals:
        void sigForkWire(QPointF);
        void sigDeleteWire();
};

class MyWire: public QObject
{
    Q_OBJECT
    public:
        MyWire(long, QPointF point1, QPointF point2);
        ~MyWire();

        QGraphicsLineItem *getLine() { return line; }
        QGraphicsTextItem *getText() { return text; }
    public slots:
        void slotForkWire(QPointF p) { emit sigForkWire(mid,p); }
        void slotDeleteWire() { emit sigDeleteWire(mid); } 
    signals:
        void sigForkWire(long, QPointF);
        void sigDeleteWire(long);
    private:
        long mid;
        MyLine *line;
        QGraphicsTextItem *text;
        // text <- depends on value from module (connect with signal)
};


#endif // GUIBLOCK_H
