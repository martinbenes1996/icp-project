
#include <iostream>

#include "debug.h"
#include "guiblock.h"
#include "window.h"


GuiBlock::GuiBlock(QPointF pos, long type, QGraphicsItem *g):
  QGraphicsPixmapItem(g), mtype(type)
{
  mrectangle = QRectF(pos.x()-mwidth/2,pos.y()-mheight/2,mwidth,mheight);
  QPixmap i( QString::fromStdString(Config::getImagePath(
        Config::getBlockName(mtype)
    )));
  i = i.scaledToHeight(mheight);
  mwidth = i.width();
  setPixmap(i);
  setPos(pos.x()-mwidth/2,pos.y()-mheight/2);

  QRectF port(pos.x()+mwidth/2, pos.y(), 100,100);
  QPainter p;
  p.setBrush( QBrush(Qt::black) );
  p.drawRect(port);

  if(Config::decodeBlockType(mtype) == BlockType::OneIn_OneOut) type = 1;
  else if(Config::decodeBlockType(mtype) == BlockType::TwoIn_OneOut) type = 2;

  //setRect(mrectangle);
  //setBrush(blockBrush);
  //setPen(blockPen);
  setAcceptDrops(true);
  setAcceptHoverEvents(true);
}

//QRectF GuiBlock::boundingRect() const { return rect(mrectangle.topLeft().x(), mrectangle.topLeft().y(), mwidth, mheight); }

void GuiBlock::paint(QPainter *p, const QStyleOptionGraphicsItem *s, QWidget *w)
{
  QGraphicsPixmapItem::paint(p,s,w);

}

void GuiBlock::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    std::cerr << "Block clicked!\n";
    MPEvent = event;
    emit sigBlockClick();
}


// block methods ---------------------------------------------

QPointF GuiBlock::getConnectorPoint(int connector)
{
    QPointF itemPoint = mrectangle.center();
    QPointF connectorPoint;

    if(type == 2)       // two_in_one_out
    {
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
            connectorPoint.setY(itemPoint.y());
        }
        /*
        else if(connector == -2)
        {
            connectorPoint.setX(itemPoint.x() + mwidth/2);
            connectorPoint.setY(itemPoint.y() + mheight/4);
        }*/
    }
    else if(type == 1)
    {
        if(connector == 0)
        {
            connectorPoint.setX(itemPoint.x() - mwidth/2);
            connectorPoint.setY(itemPoint.y());
        }
        else if(connector == -1)
        {
            connectorPoint.setX(itemPoint.x() + mwidth/2);
            connectorPoint.setY(itemPoint.y());
        }
    }
    else
    {
        std::cout << "error getConnectorPoint\n";
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
    //QPointF itemPoint = mrectangle.center();
    //QRectF tempRect1 = QRectF(itemPoint.x()-mwidth/2, itemPoint.y()-mheight/2, mwidth/2.0, mheight/2.0);
    //QRectF tempRect2 = QRectF(itemPoint.x(), itemPoint.y()-mheight/2, mwidth/2.0, mheight/2.0);
    //QRectF tempRect3 = QRectF(itemPoint.x()-mwidth/2, itemPoint.y(), mwidth/2.0, mheight/2.0);
    //QRectF tempRect4 = QRectF(itemPoint.x(), itemPoint.y(), mwidth/2.0, mheight/2.0);



    //std::cout << itemPoint.x() << itemPoint.y() << std::endl;
    //std::cout << MPEvent->pos().x() << MPEvent->pos().y() << std::endl;
    if(type == 2)       // two_in_one_out
    {
        QRectF tempRect1 = QRectF(0.0, 0.0+mheight/8.0, mwidth/2.0, mheight/4.0);
        QRectF tempRect2 = QRectF(0.0, 0.0+(mheight*5.0)/8.0, mwidth/2.0, mheight/4.0);
        QRectF tempRect3 = QRectF(0.0+(mwidth)/2.0, 0.0+(mheight)/4.0, mwidth/2.0, mheight/2.0);

        if(tempRect1.contains(MPEvent->pos().x(), MPEvent->pos().y()))
        {
            Debug::Gui("levy horni roh itemu");
            *wireFree = !input1;
            *connector = 0;
        }
        else if(tempRect2.contains(MPEvent->pos().x(), MPEvent->pos().y()))
        {
            Debug::Gui("levy dolni roh itemu");
            *wireFree = !output1;
            *connector = 1;
        }
        else if(tempRect3.contains(MPEvent->pos().x(), MPEvent->pos().y()))
        {
            Debug::Gui("pravy roh itemu");
            *wireFree = !input2;
            *connector = -1;
        }/*
        else if(tempRect4.contains(MPEvent->pos().x(), MPEvent->pos().y()))
        {
            Debug::Gui("pravy dolni roh itemu");
            *wireFree = !output2;
            *connector = -2;
        }*/
    }
    else if(type == 1)      // one_in_one_out
    {
        QRectF tempRect1 = QRectF(0.0, 0.0+mheight/4.0, mwidth/2.0, mheight/2.0);
        QRectF tempRect3 = QRectF(0.0+mwidth/2.0, 0.0+mheight/4.0, mwidth/2.0, mheight/2.0);

        if(tempRect1.contains(MPEvent->pos().x(), MPEvent->pos().y()))
        {
            Debug::Gui("levy roh itemu");
            *wireFree = !input1;
            *connector = 0;
        }
        else if(tempRect3.contains(MPEvent->pos().x(), MPEvent->pos().y()))
        {
            Debug::Gui("pravy roh itemu");
            *wireFree = !input2;
            *connector = -1;
        }
    }
    else
    {
        std::cout << "error";
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
    //QBrush b = brush();
    //b.setColor(Qt::gray);
    //setBrush(b);
}
void GuiBlock::hoverLeaveEvent(QGraphicsSceneHoverEvent*)
{
    //std::cerr << "leave\n";
    //QBrush b = brush();
    //b.setColor(Qt::darkGray);
    //setBrush(blockBrush);
}



MyWire::MyWire(long id, QPointF point1, QPointF point2, std::shared_ptr<GuiBlock> gb1, ptr::shared_ptr<GuiBlock> gb2): mid(id)
{
    for(auto& it: MyWire::splitLine(point1, point2))
    {
        std::shared_ptr<MyLine> l = std::make_shared<MyLine>(it.first, it.second);
        l->setPen(QPen(QBrush(Qt::darkGray, Qt::SolidPattern), 2));
        QObject::connect(l.get(), SIGNAL(sigForkWire(QPointF)),
                        this, SLOT(slotForkWire(QPointF)));
        QObject::connect(l.get(), SIGNAL(sigDeleteWire()),
                        this, SLOT(slotDeleteWire()));
        mLines.push_back(l);
    }

    gblock1 = gb1;
    gblock2 = gb2;

    mtext = std::make_shared<QGraphicsTextItem>();
    mtext->setPos( (point1.x()+point2.x())/2, (point1.y()+point2.y())/2 );
    mtext->setPlainText("0");
    mtext->setDefaultTextColor(Qt::cyan);

    QFont font = QFont();
    font.setPixelSize(12);
    mtext->setFont(font);

}

std::vector<std::pair<QPointF,QPointF>> MyWire::splitLine(QPointF s, QPointF f)
{
    std::vector<std::pair<QPointF,QPointF>> v;
    double dx = (f.x()-s.x())/2.0;
    double dy = (f.y()-s.y());
    QPointF p1(s.x()+dx, s.y());
    QPointF p2(s.x()+dx, s.y()+dy);
    std::cout << s.x() << " " << s.y() << ", " << f.x() << " " << f.y() << "\n";
    std::cout << dx << " " << dy << "\n";
    v.push_back( std::make_pair(s, p1) );
    v.push_back( std::make_pair(p1, p2) );
    v.push_back( std::make_pair(p2, f) );
    return v;
}

