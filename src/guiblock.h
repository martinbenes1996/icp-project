// guiblock.h
// Autoři: xbenes49, xpolan09
// Projekt do předmětu ICP.
// Datum: 29.04.5018


#ifndef GUIBLOCK_H
#define GUIBLOCK_H

#include <iostream>
#include <memory>
#include <string>

#include <QWidget>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEllipseItem>
#include <QPointF>
#include <QRectF>
#include <QBrush>
#include <QPen>
#include <QLineF>
#include <QToolTip>

#include "defs.h"

class GuiBlock: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
  public:
    GuiBlock(QPointF, long, QGraphicsItem* g = 0);

    /**
     * @brief   Gets type of the block.
     * @returns type of the block represented by integer
     */
    long getType() { return mtype; }

    // QRectF boundingRect() const override;
    /**
     * @brief   Function that paints the block.
     */
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;

    void mousePressEvent(QGraphicsSceneMouseEvent*) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent*) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*) override;

    void contains(QPointF);

    /**
     * @brief   Gets last mouse press event.
     * @returns pointer to last mouse press event
     */
    QGraphicsSceneMouseEvent * getMouseEvent() { return MPEvent; }

    // methods for different blocks
    /**
     * @brief   Determines which connector of the block was clicked and whether the block is free.
     * @param   connector   pointer to a integer representing connectors
     * @param   wireFree    pointer to integer representing availability of the connector
     * @returns connector and availability of the connector through pointers
     */
    void getPointFromBlock(int *, bool *);
    /**
     * @brief   Gets point in scene asociated with a connector.
     * @param   connector   integer representing connector of a block
     * @returns point in scene
     */
    QPointF getConnectorPoint(int);

    /**
     * @brief   Sets connector availability.
     * @param   connector   integer representing connector
     * @param   addWire     true -> set not available, false -> set available
     */
    void setConnectorAvailability(int, bool);

    /**
     * @brief   Prints connector availability of a block. Debug function.
     */
    void printCon() { std::cout << input1<<input2<<output1<<output2<<"\n"; }

    void setValue(Value v) { mvalue = v; setToolTip(QString::fromStdString("Value: "+std::to_string(mvalue.value)+" Type: "+mvalue.type));}

    void setColor(bool active);
    // ----------------------------

  signals:
    void sigBlockClick();

  private:
    QRectF mrectangle;/*
    QBrush brush;
    QPen pen;*/
    double mwidth = 30;     /**< Width of the block. */
    double mheight = 60;    /**< Height of the block. */

    QGraphicsSceneMouseEvent * MPEvent = nullptr;   /**< Last mouse press event. */

    // different blocks variables - I/O
    long mtype;     /**< Type of the block. */
    Value mvalue;

    QBrush blockBrush;
    QPen blockPen;

    /**< Input and output connector availability. */
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

class GuiInput;
class MyWire: public QObject
{
    Q_OBJECT
    public:
        MyWire(long, QPointF point1, QPointF point2, std::shared_ptr<GuiBlock> gb1, std::shared_ptr<GuiBlock> gb2, int connector1, int connector2);
        MyWire(long, QPointF point1, QPointF point2, std::shared_ptr<GuiInput> gb1, std::shared_ptr<GuiBlock> gb2, int connector1, int connector2);
        MyWire(long, QPointF point1, QPointF point2, std::shared_ptr<GuiBlock> gb1, std::shared_ptr<GuiInput> gb2, int connector1, int connector2);

        std::vector<std::shared_ptr<MyLine>> getLine() { return mLines; }
        QGraphicsTextItem *getText() { return mtext.get(); }
        std::shared_ptr<GuiInput> getIBlock1() { return iblock1; }
        std::shared_ptr<GuiBlock> getBlock1() { return gblock1; }
        std::shared_ptr<GuiInput> getIBlock2() { return iblock2; }
        std::shared_ptr<GuiBlock> getBlock2() { return gblock2; }
        int getConnector1() { return mconnector1; }
        int getConnector2() { return mconnector2; }
        //void setValue(Value v) { mvalue = v; }
        void setValue(Value v);
        // if active is true, it sets color of the wire to red, else black
        void setColor(bool active);
    public slots:
        void slotForkWire(QPointF p) { emit sigForkWire(mid,p); }
        void slotDeleteWire() { emit sigDeleteWire(mid); }
    signals:
        void sigForkWire(long, QPointF);
        void sigDeleteWire(long);
    private:
        Value mvalue;
        long mid;
        std::vector<std::shared_ptr<MyLine>> mLines;
        std::shared_ptr<QGraphicsTextItem> mtext;
        static std::vector<std::pair<QPointF,QPointF>> splitLine(QPointF, QPointF);
        // text <- depends on value from module (connect with signal)
        std::shared_ptr<GuiInput> iblock1 = nullptr;
        std::shared_ptr<GuiBlock> gblock1 = nullptr;
        std::shared_ptr<GuiInput> iblock2 = nullptr;
        std::shared_ptr<GuiBlock> gblock2 = nullptr;
        int mconnector1;
        int mconnector2;
};

class GuiInput: public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
    public:
        GuiInput(QPointF pos, QGraphicsItem* g = 0);

        Value getValue() { return mvalue; }
        void setValue(Value v) { mvalue = v; }

        void mousePressEvent(QGraphicsSceneMouseEvent*) override;
        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*) override;
        void hoverEnterEvent(QGraphicsSceneHoverEvent*) override;
        void hoverLeaveEvent(QGraphicsSceneHoverEvent*) override;
        void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;

        bool isOk() { return mok; }

        /**
         * @brief   Gets last mouse press event.
         * @returns pointer to last mouse press event
         */
        QGraphicsSceneMouseEvent * getMouseEvent() { return MPEvent; }

        void getPointFromBlock(int *connector, bool *wireFree);
        QPointF getConnectorPoint(int connector);
        /**
         * @brief   Sets connector availability.
         * @param   connector   integer representing connector
         * @param   addWire     true -> set not available, false -> set available
         */
        void setConnectorAvailability(int, bool);

    signals:
        void sigBlockClick();
    private:
        void getUserValue(double *value, std::string &type, bool *mok);

        Value mvalue;
        double mradius = 30;
        bool mok;
        QPointF positionCenter;
        bool output1 = false;

        QGraphicsSceneMouseEvent * MPEvent = nullptr;

        void showValueDialog();

        //std::shared_ptr<QLabel> label = nullptr;
};


#endif // GUIBLOCK_H
