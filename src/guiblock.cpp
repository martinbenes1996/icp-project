
#include <iostream>

#include "guiblock.h"
#include "window.h"


GuiBlock::GuiBlock(QPointF pos, int typeOfBlock, QGraphicsItem *g):
  QGraphicsRectItem(g)
{
  mrectangle = QRectF(pos.x()-mwidth/2,pos.y()-mheight/2,mwidth,mheight);
  type = typeOfBlock;

  // different types of blocks
  if(type == 0)         // scitacka -> 2I1O
  {
    blockBrush = QBrush(Qt::red, Qt::SolidPattern);
    blockPen = QPen(blockBrush, 1);

    output2 = true;     // blocks second output
  }
  else if(type == 1)    // nasobicka -> 2I1O
  {
    blockBrush = QBrush(Qt::green, Qt::SolidPattern);
    blockPen = QPen(blockBrush, 1);

    output2 = true;
  }
  else if(type == 2)    // odmocnovacka -> 1I1O
  {
    blockBrush = QBrush(Qt::blue, Qt::SolidPattern);
    blockPen = QPen(blockBrush, 1);

    input2 = true;
    output2 = true;
  }
  else
  {
    blockBrush = QBrush(Qt::darkGray, Qt::SolidPattern);
    blockPen = QPen(blockBrush, 1);
  }


  setRect(mrectangle);
  setBrush(blockBrush);
  setPen(blockPen);
  setAcceptDrops(true);
  setAcceptHoverEvents(true);
}

//QRectF GuiBlock::boundingRect() const { return rect(mrectangle.topLeft().x(), mrectangle.topLeft().y(), mwidth, mheight); }

void GuiBlock::paint(QPainter *p, const QStyleOptionGraphicsItem *s, QWidget *w)
{
  QGraphicsRectItem::paint(p,s,w);

}

void GuiBlock::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    //std::cerr << "...!\n";
    MPEvent = event;
    emit sigBlockClick();
}

// block methods ---------------------------------------------

QPointF GuiBlock::getConnectorPoint(int connector)
{
    QPointF itemPoint = mrectangle.center();
    QPointF connectorPoint;

    if(connector == 0)
    {
        connectorPoint.setX(itemPoint.x() - mwidth/2);
        connectorPoint.setY(itemPoint.y() - mheight/4);
    }
    else if(connector == 1)
    {
        connectorPoint.setX(itemPoint.x() - mwidth/2);
        connectorPoint.setY(itemPoint.y() + mheight/4);
    }
    else if(connector == -1)
    {
        connectorPoint.setX(itemPoint.x() + mwidth/2);
        connectorPoint.setY(itemPoint.y() - mheight/4);
    }
    else if(connector == -2)
    {
        connectorPoint.setX(itemPoint.x() + mwidth/2);
        connectorPoint.setY(itemPoint.y() + mheight/4);
    }

    return connectorPoint;
}/*
QPointF GuiBlock::getInput_2Point()
{
    QPointF itemPoint = mrectangle.center();
    QPointF input2;

    input2.setX(itemPoint.x() - mwidth/2);
    input2.setY(itemPoint.y() + mheight/4);

    return input2;
}
QPointF GuiBlock::getOutput_1Point()
{
    QPointF itemPoint = mrectangle.center();
    QPointF output1;

    output1.setX(itemPoint.x() + mwidth/2);
    output1.setY(itemPoint.y() - mheight/4);

    return output1;
}
QPointF GuiBlock::getOutput_2Point()
{
    QPointF itemPoint = mrectangle.center();
    QPointF output2;

    output2.setX(itemPoint.x() + mwidth/2);
    output2.setY(itemPoint.y() + mheight/4);

    return output2;
}*/

void GuiBlock::getPointFromBlock(int *connector, bool *wireFree)
{
    //std::cout << "getPoint_2I1O: im here!\n";
    QPointF itemPoint = mrectangle.center();
    QRectF tempRect1 = QRectF(itemPoint.x()-mwidth/2, itemPoint.y()-mheight/2, mwidth/2.0, mheight/2.0);
    QRectF tempRect2 = QRectF(itemPoint.x(), itemPoint.y()-mheight/2, mwidth/2.0, mheight/2.0);
    QRectF tempRect3 = QRectF(itemPoint.x()-mwidth/2, itemPoint.y(), mwidth/2.0, mheight/2.0);
    QRectF tempRect4 = QRectF(itemPoint.x(), itemPoint.y(), mwidth/2.0, mheight/2.0);

    //std::cout << itemPoint.x() << itemPoint.y() << std::endl;
    if(tempRect1.contains(MPEvent->pos().x(), MPEvent->pos().y()))
    {
        *wireFree = !input1;
        *connector = 0;
        std::cout << "levy horni roh itemu!\n";
        return;
    }
    else if(tempRect2.contains(MPEvent->pos().x(), MPEvent->pos().y()))
    {
        *wireFree = !output1;
        *connector = -1;
        std::cout << "pravy horni roh itemu!\n";
        return;
    }
    else if(tempRect3.contains(MPEvent->pos().x(), MPEvent->pos().y()))
    {
        *wireFree = !input2;
        *connector = 1;
        std::cout << "levy dolni roh itemu!\n";
        return;
    }
    else if(tempRect4.contains(MPEvent->pos().x(), MPEvent->pos().y()))
    {
        *wireFree = !output2;
        *connector = -2;
        std::cout << "pravy dolni roh itemu!\n";
        return;
    }
}

void GuiBlock::setConnectorAvailability(int connector, bool addWire)
{
    if(connector == 0)
    {
        if(addWire) input1 = true;
        else input1 = false;
    }
    else if(connector == 1)
    {
        if(addWire) input2 = true;
        else input2 = false;
    }
    else if(connector == -1)
    {
        if(addWire) output1 = true;
        else output1 = false;
    }
    else if(connector == -2)
    {
        if(addWire) output2 = true;
        else output2 = false;
    }
}

void GuiBlock::hoverEnterEvent(QGraphicsSceneHoverEvent*)
{
    //std::cerr << "enter\n";
    QBrush b = brush();
    b.setColor(Qt::gray);
    setBrush(b);
}
void GuiBlock::hoverLeaveEvent(QGraphicsSceneHoverEvent*)
{
    //std::cerr << "leave\n";
    //QBrush b = brush();
    //b.setColor(Qt::darkGray);
    setBrush(blockBrush);
}



/* wire is here for now *//*
MyLine::mousePressEvent(QGraphicsSceneMousePressEvent *event)
{
    MPEvent = event;
    emit sigWireClick();
}*/

MyWire::MyWire(QPointF point1, QPointF point2)
{
    line = new QGraphicsLineItem(point1.x(), point1.y(), point2.x(), point2.y());
    line->setPen(QPen(QBrush(Qt::darkGray, Qt::SolidPattern), 2));

    text = new QGraphicsTextItem;
    text->setPos( (point1.x()+point2.x())/2, (point1.y()+point2.y())/2 );
    text->setPlainText("0");
    text->setDefaultTextColor(Qt::cyan);

    QFont font = QFont();
    font.setPixelSize(12);
    text->setFont(font);

}
MyWire::~MyWire()
{
    delete line;
    delete text;
}

