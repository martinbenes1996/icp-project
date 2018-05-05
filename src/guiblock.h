
/**
 * @file guiblock.h
 * @author xbenes49, xpolan09
 * @date 5 May 2018
 * @brief graphical objects interface
 *
 * This module contains graphical objects definitions.
 */

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

/**
 * @brief Graphical block.
 */
class GuiBlock: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
  public:
    /**
     * @brief GuiBlock constructor.
     */
    GuiBlock(QPointF, long, QGraphicsItem* g = 0);

    /**
     * @brief   Gets type of the block.
     * @returns Type of the block.
     */
    long getType() { return mtype; }
    /**
     * @brief   Width getter.
     * @returns Width of the block.
     */
    long getWidth() { return mwidth; }
    /**
     * @brief   Height getter.
     * @returns Height of the block.
     */
    long getHeight() { return mheight; }

    /**
     * @brief   Function that paints the block.
     * @param p     Painter to paint.
     * @param s     Style to paint.
     * @param g     Parent.
     */
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;

    /**
     * @brief   Mouse press handler.
     * @param event     Description of event.
     */     
    void mousePressEvent(QGraphicsSceneMouseEvent*) override;
    /**
     * @brief   Mouse enter handler.
     * @param event     Description of event.
     */
    void hoverEnterEvent(QGraphicsSceneHoverEvent*) override;
    /**
     * @brief   Mouse leave handler.
     * @param event     Description of event.
     */
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*) override;

    /**
     * @brief Returns, weather the point is inside the block.
     * @param p         Point.
     */
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

    /**
     * @brief   Value setter
     * @param v         Value to set.
     */        
    void setValue(Value v);
    /**
     * @brief   Color setter.
     * @param active    True, if highlight.
     */
    void setColor(bool active);
    // ----------------------------

  signals:
    /**
     * @brief   Emitted, if block clicked.
     */
    void sigBlockClick();

  private:
    QRectF mrectangle;      /**< Rectangle of the block. */
    double mwidth = 30;     /**< Width of the block. */
    double mheight = 60;    /**< Height of the block. */

    QGraphicsSceneMouseEvent * MPEvent = nullptr;   /**< Last mouse press event. */

    // different blocks variables - I/O
    long mtype;     /**< Type of the block. */
    long mporttype; /**< Port type of the block. */
    Value mvalue;   /**< Assigned value. */

    QBrush blockBrush;  /**< Brush. */
    QPen blockPen;      /**< Pen. */

    /**< Input and output connector availability. */
    bool input1 = false;    /**< Availability of input 1. */
    bool input2 = false;    /**< Availability of input 2. */
    bool output1 = false;   /**< Availability of output 1. */
    bool output2 = false;   /**< Availability of output 2. */
};

/**
 * @brief Line, wire segment.
 */
class MyLine: public QObject, public QGraphicsLineItem
{
    Q_OBJECT

    public:
        /**
         * @brief MyLine constructor.
         * @param s         Start point.
         * @param f         End point.
         * @param parent    Parent.
         */
        MyLine(QPointF s, QPointF f, QGraphicsItem* parent = 0):
            QGraphicsLineItem(s.x(), s.y(), f.x(), f.y(), parent) {}

        /**
         * @brief   Mouse press handler.
         * @param event     Description of event.
         */ 
        void mousePressEvent(QGraphicsSceneMouseEvent* event)
        {
            if(event->button() == Qt::LeftButton) { emit sigForkWire(event->pos()); }
            else if(event->button() == Qt::RightButton) { emit sigDeleteWire(); }
        }

    signals:
        /**
         * @brief Fork the wire.
         */
        void sigForkWire(QPointF);
        /**
         * @brief Delete the wire.
         */
        void sigDeleteWire();
};

class GuiInput;

/**
 * @brief Graphical wire.
 */
class MyWire: public QObject
{
    Q_OBJECT
    public:
        /**
         * @brief MyWire constructor for two GuiBlocks connected.
         * @param id            Wire ID.
         * @param point1        Start point.
         * @param point2        End point.
         * @param gb1           Start block.
         * @param gb2           End block.
         * @param connector1    Start block connector.
         * @param connector2    End block connector.
         */
        MyWire(long, QPointF point1, QPointF point2, std::shared_ptr<GuiBlock> gb1, std::shared_ptr<GuiBlock> gb2, int connector1, int connector2);
        /**
         * @brief MyWire constructor for wire from GuiInput to GuiBlock.
         * @param id            Wire ID.
         * @param point1        Start point.
         * @param point2        End point.
         * @param gb1           Start input.
         * @param gb2           End block.
         * @param connector1    Start input connector.
         * @param connector2    End block connector.
         */
        MyWire(long, QPointF point1, QPointF point2, std::shared_ptr<GuiInput> gb1, std::shared_ptr<GuiBlock> gb2, int connector1, int connector2);
        /**
         * @brief MyWire constructor for wire from GuiBlock to GuiInput.
         * @param id            Wire ID.
         * @param point1        Start point.
         * @param point2        End input.
         * @param gb1           Start block.
         * @param gb2           End input.
         * @param connector1    Start block connector.
         * @param connector2    End input connector.
         */
        MyWire(long, QPointF point1, QPointF point2, std::shared_ptr<GuiBlock> gb1, std::shared_ptr<GuiInput> gb2, int connector1, int connector2);

        /**
         * @brief Line getter.
         * @returns Vector of lines, wire is composed of.
         */
        std::vector<std::shared_ptr<MyLine>> getLine() { return mLines; }
        /**
         * @brief Text getter.
         * @returns Text.
         */
        QGraphicsTextItem *getText() { return mtext.get(); }

        /**
         * @brief Input1 getter.
         * @returns Start input.
         */
        std::shared_ptr<GuiInput> getIBlock1() { return iblock1; }
        /**
         * @brief Block1 getter.
         * @returns Start block.
         */
        std::shared_ptr<GuiBlock> getBlock1() { return gblock1; }
        /**
         * @brief Input1 getter.
         * @returns End input.
         */
        std::shared_ptr<GuiInput> getIBlock2() { return iblock2; }
        /**
         * @brief Block1 getter.
         * @returns End block.
         */
        std::shared_ptr<GuiBlock> getBlock2() { return gblock2; }

        /**
         * @brief Connector1 getter.
         * @returns Start block/input connector.
         */
        int getConnector1() { return mconnector1; }
        /**
         * @brief Connector2 getter.
         * @returns End block/input connector.
         */
        int getConnector2() { return mconnector2; }
        /**
         * @brief Saved point 1 getter.
         * @returns 1st saved point.
         */
        QPointF getSavedPoint1() { return msavedPoint1; }
        /**
         * @brief Saved point 2 getter.
         * @returns 2nd saved point.
         */
        QPointF getSavedPoint2() { return msavedPoint2; }

        /**
         * @brief Value setter.
         * @param v     New value.
         */
        void setValue(Value v);
        /**
         * @brief Highlights the wire, if active is true.
         * @param active        Set highlighted, if active is true.
         */
        void setColor(bool active);

    public slots:
        /**
         * @brief Received, when the wire should be forked.
         * @param p         Position of fork.
         */
        void slotForkWire(QPointF p) { emit sigForkWire(mid,p); }
        /**
         * @brief Received, when the wire should be deleted.
         */
        void slotDeleteWire() { emit sigDeleteWire(mid); }

    signals:
        /**
         * @brief Emitted, when th wire should be forked.
         * @param id        Id of the wire.
         * @oaram p         Position of the fork.
         */
        void sigForkWire(long, QPointF);
        /**
         * @brief Emitted, when the wire should be deleted.
         * @param id        Id of the wire being deleted.
         */
        void sigDeleteWire(long);

    private:
        Value mvalue; /**< Value, that wire has. */
        long mid; /**< ID of the wire. */
        std::vector<std::shared_ptr<MyLine>> mLines; /**< Lines, wire is composed from. */
        std::shared_ptr<QGraphicsTextItem> mtext; /**< Text over the wire. */
        std::shared_ptr<GuiInput> iblock1 = nullptr; /**< Start input. */
        std::shared_ptr<GuiBlock> gblock1 = nullptr; /**< Start block. */
        std::shared_ptr<GuiInput> iblock2 = nullptr; /**< End input. */
        std::shared_ptr<GuiBlock> gblock2 = nullptr; /**< End block. */
        QPointF msavedPoint1; /**< Saved point 1. */
        QPointF msavedPoint2; /**< Saved point 2. */
        int mconnector1; /**< Connector on the start block, wire is connected to. */
        int mconnector2; /**< Connector of the end block, wire is connected to.. */

        /**
         * @brief Counts the split points for the given start and end.
         * @param start         Start point.
         * @param end           End point.
         * @returns Vector of lines, that represent the split.
         */
        static std::vector<std::pair<QPointF,QPointF>> splitLine(QPointF, QPointF);

};

/**
 * @brief Graphical input.
 */
class GuiInput: public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
    public:
        /**
         * @brief GuiInput constructor.
         * @param pos       Position of the input.
         * @param load      Open input dialog, if true.
         * @param g         Parent.
         */ 
        GuiInput(QPointF pos, bool load = false, QGraphicsItem* g = 0);

        /**
         * @brief Value getter.
         * @returns value of the input.
         */
        Value getValue() { return mvalue; }
        /**
         * @brief Value setter.
         * @param v         New value.
         */
        void setValue(Value v) { mvalue = v; setToolTip(QString::fromStdString("Value: "+std::to_string(mvalue.value)+"\nType: "+mvalue.type));}

        /**
         * @brief   Mouse press handler.
         * @param event     Description of event.
         */ 
        void mousePressEvent(QGraphicsSceneMouseEvent*) override;
        /**
         * @brief   Mouse double click handler.
         * @param event     Description of event.
         */ 
        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*) override;
        /**
         * @brief   Mouse enter handler.
         * @param event     Description of event.
         */ 
        void hoverEnterEvent(QGraphicsSceneHoverEvent*) override;
        /**
         * @brief   Mouse leave handler.
         * @param event     Description of event.
         */ 
        void hoverLeaveEvent(QGraphicsSceneHoverEvent*) override;
        /**
         * @brief   Function that paints the block.
         * @param p     Painter to paint.
         * @param s     Style to paint.
         * @param g     Parent.
         */
        void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;

        /**
         * @brief Status indicator (used in input dialog in constructor).
         * @returns If the input was correct, returns true.
         */
        bool isOk() { return mok; }
        /**
         * @brief Type getter.
         * @returns Type.
         */
        long getType() { return -1; }
        /**
         * @brief Port type getter.
         * @returns Port type.
         */
        long getPortType() { return mporttype; }
        /**
         * @brief Radius getter.
         * @returns Radius.
         */
        long getRadius() { return mradius; }
        /**
         * @brief Position center getter.
         * @returns Position center.
         */
        QPointF getPositionCenter() { return positionCenter; }

        /**
         * @brief   Gets last mouse press event.
         * @returns pointer to last mouse press event
         */
        QGraphicsSceneMouseEvent * getMouseEvent() { return MPEvent; }

        /**
         * @brief Counts point from the block.
         * @param connector         The connector to connect to.
         * @param wireFree          Status (false, if fail).
         */
        void getPointFromBlock(int *connector, bool *wireFree);
        /**
         * @brief Returns position of the connector.
         * @param connector         Connector.
         * @returns Connector's position.
         */
        QPointF getConnectorPoint(int connector);
        /**
         * @brief   Sets connector availability.
         * @param   connector   integer representing connector
         * @param   addWire     true -> set not available, false -> set available
         */
        void setConnectorAvailability(int, bool);

    signals:
        /**
         * @brief Emitted, when block clicked.
         */
        void sigBlockClick();
        /**
         * @brief Emitted, when value changes.
         */
        void sigValueChanged();
    private:
        /**
         * @brief Opens dialog and reads input from the user.
         * @param value         New value read.
         * @param type          Type read.
         * @param mok           Status.
         */
        void getUserValue(double *value, std::string &type, bool *mok);
        /**
         * @brief Shows the dialog with the value.
         */
        void showValueDialog();

        Value mvalue; /**< Value. */
        int mporttype = -1; /**< Type of the ports (block specific). */
        double mradius = 30; /**< Radius. */
        bool mok;   /**< Status of input. */
        QPointF positionCenter; /**< Center point. */
        bool output1 = false; /**< Output status. */

        QGraphicsSceneMouseEvent * MPEvent = nullptr; /**< Last mouse event. */

};


#endif // GUIBLOCK_H
