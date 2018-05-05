
/**
 * @file guiblock.cpp
 * @author xbenes49, xpolan09
 * @date 5 May 2018
 * @brief Graphical objects module
 *
 * This module contains graphical objects implementations.
 */

#include <iostream>

#include <QInputDialog>
#include <QLabel>
#include <QStringList>
#include <QLineEdit>
#include <QDialog>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QComboBox>
#include <math.h>

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

  if(Config::decodeBlockType(type) == BlockType::OneIn_OneOut)
  {
    mporttype = 1;
    input2 = true;
    output2 = true;
  }
  else if(Config::decodeBlockType(type) == BlockType::TwoIn_OneOut)
  {
    mporttype = 2;
    output2 = true;
  }

  mvalue.valid = false;
  setToolTip(QString::fromStdString("Value: Not defined\nType: Not defined"));


  setAcceptDrops(true);
  setAcceptHoverEvents(true);
}

void GuiBlock::paint(QPainter *p, const QStyleOptionGraphicsItem *s, QWidget *w)
{
  QGraphicsPixmapItem::paint(p,s,w);
}

void GuiBlock::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    Debug::Events("Block clicked!");
    MPEvent = event;
    emit sigBlockClick();
}


// block methods ---------------------------------------------

QPointF GuiBlock::getConnectorPoint(int connector)
{
    QPointF itemPoint = mrectangle.center();
    QPointF connectorPoint;

    if(mporttype == 2)       // two_in_one_out
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
    }
    else if(mporttype == 1)
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
        //std::cout << "error getConnectorPoint\n";
    }

    return connectorPoint;
}

void GuiBlock::getPointFromBlock(int *connector, bool *wireFree)
{
    if(mporttype == 2)       // two_in_one_out
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
            *wireFree = !input2;
            *connector = 1;
        }
        else if(tempRect3.contains(MPEvent->pos().x(), MPEvent->pos().y()))
        {
            Debug::Gui("pravy roh itemu");
            *wireFree = !output1;
            *connector = -1;
        }
    }
    else if(mporttype == 1)      // one_in_one_out
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
            *wireFree = !output1;
            *connector = -1;
        }
    }
    else
    {
        //std::cout << "error getpointfromblock\n";
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

void GuiBlock::setValue(Value v)
{
    mvalue = v;
    if(v.valid)
    {
        setToolTip(QString::fromStdString("Value: "+std::to_string(mvalue.value)+"\nType: "+mvalue.type));
    }
    else
    {
        setToolTip(QString::fromStdString("Value: Not defined\nType: Not defined"));
    }
}

void GuiBlock::setColor(bool active)
{
    if(active)
    {
        QPixmap i( QString::fromStdString(Config::getHLImagePath(
                    Config::getBlockName(mtype)
        )));
        i = i.scaledToHeight(mheight);
        mwidth = i.width();
        setPixmap(i);
    }
    else
    {
        QPixmap i( QString::fromStdString(Config::getImagePath(
                    Config::getBlockName(mtype)
        )));
        i = i.scaledToHeight(mheight);
        mwidth = i.width();
        setPixmap(i);
    }
}

void GuiBlock::hoverEnterEvent(QGraphicsSceneHoverEvent*) {}
void GuiBlock::hoverLeaveEvent(QGraphicsSceneHoverEvent*) {}

MyWire::MyWire(long id, QPointF point1, QPointF point2, std::shared_ptr<GuiBlock> gb1, std::shared_ptr<GuiBlock> gb2, int connector1, int connector2): mid(id)
{
    for(auto& it: MyWire::splitLine(point1, point2))
    {
        std::shared_ptr<MyLine> l = std::make_shared<MyLine>(it.first, it.second);
        l->setPen(QPen(QBrush(Qt::darkGray, Qt::SolidPattern), 3));
        QObject::connect(l.get(), SIGNAL(sigForkWire(QPointF)),
                        this, SLOT(slotForkWire(QPointF)));
        QObject::connect(l.get(), SIGNAL(sigDeleteWire()),
                        this, SLOT(slotDeleteWire()));
        mLines.push_back(l);
        l.get()->setToolTip(QString::fromStdString("Value: Not defined\nType: Not defined"));
    }

    gblock1 = gb1;
    gblock2 = gb2;

    msavedPoint1 = point1;
    msavedPoint2 = point2;

    mconnector1 = connector1;
    mconnector2 = connector2;

    mtext = std::make_shared<QGraphicsTextItem>();
    mtext->setPos( /*(point1.x()+point2.x())/2 - abs(point2.x()-point1.x())/3*/ std::min(point1.x(), point2.x()), (point1.y()+point2.y())/2 );
    mtext->setTextWidth(abs(point1.x()-point2.x()));
    mtext->setHtml("<center>N</center>");
    mtext->setDefaultTextColor(Qt::green);

    QFont font = QFont();
    font.setPixelSize(12);
    mtext->setFont(font);

    mvalue.valid = false;

}

MyWire::MyWire(long id, QPointF point1, QPointF point2, std::shared_ptr<GuiInput> gb1, std::shared_ptr<GuiBlock> gb2, int connector1, int connector2): mid(id)
{
    for(auto& it: MyWire::splitLine(point1, point2))
    {
        std::shared_ptr<MyLine> l = std::make_shared<MyLine>(it.first, it.second);
        l->setPen(QPen(QBrush(Qt::darkGray, Qt::SolidPattern), 3));
        QObject::connect(l.get(), SIGNAL(sigForkWire(QPointF)),
                        this, SLOT(slotForkWire(QPointF)));
        QObject::connect(l.get(), SIGNAL(sigDeleteWire()),
                        this, SLOT(slotDeleteWire()));
        mLines.push_back(l);
        l.get()->setToolTip(QString::fromStdString("Value: Not defined\nType: Not defined"));
    }

    iblock1 = gb1;
    gblock2 = gb2;

    msavedPoint1 = point1;
    msavedPoint2 = point2;

    mconnector1 = connector1;
    mconnector2 = connector2;

    mtext = std::make_shared<QGraphicsTextItem>();
    mtext->setPos( /*(point1.x()+point2.x())/2 - abs(point2.x()-point1.x())/3*/ std::min(point1.x(), point2.x()), (point1.y()+point2.y())/2 );
    mtext->setTextWidth(abs(point1.x()-point2.x()));
    mtext->setHtml("<center>N</center>");
    mtext->setDefaultTextColor(Qt::green);

    QFont font = QFont();
    font.setPixelSize(12);
    mtext->setFont(font);

    mvalue.valid = false;

}
MyWire::MyWire(long id, QPointF point1, QPointF point2, std::shared_ptr<GuiBlock> gb1, std::shared_ptr<GuiInput> gb2, int connector1, int connector2): mid(id)
{
    for(auto& it: MyWire::splitLine(point1, point2))
    {
        std::shared_ptr<MyLine> l = std::make_shared<MyLine>(it.first, it.second);
        l->setPen(QPen(QBrush(Qt::darkGray, Qt::SolidPattern), 3));
        QObject::connect(l.get(), SIGNAL(sigForkWire(QPointF)),
                        this, SLOT(slotForkWire(QPointF)));
        QObject::connect(l.get(), SIGNAL(sigDeleteWire()),
                        this, SLOT(slotDeleteWire()));
        mLines.push_back(l);
        l.get()->setToolTip(QString::fromStdString("Value: Not defined\nType: Not defined"));
    }

    gblock1 = gb1;
    iblock2 = gb2;

    msavedPoint1 = point1;
    msavedPoint2 = point2;

    mconnector1 = connector1;
    mconnector2 = connector2;

    mtext = std::make_shared<QGraphicsTextItem>();
    mtext->setPos( /*(point1.x()+point2.x())/2 - abs(point2.x()-point1.x())/3*/ std::min(point1.x(), point2.x()), (point1.y()+point2.y())/2 );
    mtext->setTextWidth(abs(point1.x()-point2.x()));
    mtext->setHtml("<center>N</center>");
    mtext->setDefaultTextColor(Qt::green);

    QFont font = QFont();
    font.setPixelSize(12);
    mtext->setFont(font);

    mvalue.valid = false;

}

void MyWire::setColor(bool active)
{
    for(auto x: mLines)
    {
        if(active)
        {
            QPen p = QPen(QBrush(Qt::red, Qt::SolidPattern), 3);
            x.get()->setPen(p);
        }
        else
        {
            x.get()->setPen(QPen(QBrush(Qt::darkGray, Qt::SolidPattern), 3));
        }
    }
}

void MyWire::setValue(Value v)
{
    mvalue = v;
    if(v.valid)
    {
        mtext->setHtml(QString::fromStdString("<center>"+std::to_string(v.value)+"</center>"/*+" "+v.type*/));
        //mtext->setPlainText(QString::fromStdString(std::to_string(v.value)/*+" "+v.type*/));
        for(auto& it: mLines)
        {
            it.get()->setToolTip(QString::fromStdString("Value: "+std::to_string(mvalue.value)+"\nType: "+mvalue.type));
        }
    }
    else
    {
        mtext->setHtml("<center>N</center>");
        for(auto& it: mLines)
        {
            it.get()->setToolTip(QString::fromStdString("Value: Not defined\nType: Not defined"));
        }
    }
}

std::vector<std::pair<QPointF,QPointF>> MyWire::splitLine(QPointF s, QPointF f)
{
    std::vector<std::pair<QPointF,QPointF>> v;
    double dx = (f.x()-s.x())/2.0;
    double dy = (f.y()-s.y());
    QPointF p1(s.x()+dx, s.y());
    QPointF p2(s.x()+dx, s.y()+dy);
    //std::cout << s.x() << " " << s.y() << ", " << f.x() << " " << f.y() << "\n";
    //std::cout << dx << " " << dy << "\n";
    v.push_back( std::make_pair(s, p1) );
    v.push_back( std::make_pair(p1, p2) );
    v.push_back( std::make_pair(p2, f) );
    return v;
}

GuiInput::GuiInput(QPointF pos, bool load, QGraphicsItem* g):
    QGraphicsEllipseItem(g)
{
    Debug::Gui("GuiInput::GuiInput");
    setBrush(QBrush(Qt::black));
    setRect(pos.x()-mradius/2,pos.y()-mradius/2, mradius, mradius);
    positionCenter = pos;

    // show input value dialog
    if(!load)
    {
        getUserValue(&mvalue.value, mvalue.type, &mok);
        mvalue.valid = true;

        setToolTip(QString::fromStdString("Value: "+std::to_string(mvalue.value)+"\nType: "+mvalue.type));
    }
    else
    {
        //setToolTip(QString::fromStdString("Value: Not defined\nType: Not defined"));
    }
    //std::cout << value << " " << type << std::endl;



    setAcceptDrops(true);
    setAcceptHoverEvents(true);
}


void GuiInput::getUserValue(double *value, std::string &type, bool *mok)
{
    *value = 0.0;
    int typeIdx = 0;

    QDialog dialog;
    QFormLayout form(&dialog);

    dialog.setWindowTitle("Input value dialog");

    std::shared_ptr<QLineEdit> line = std::make_shared<QLineEdit>(&dialog);
    QString label = QString("Input value: ");
    form.addRow(label, line.get());

    QString label2 = QString("Input type: ");
    QComboBox box;
    for(auto& it: Config::getTypes())
    {
        box.addItem(QString::fromStdString(it));
    }
    form.addRow(label2, &box);

    QPushButton *okButton = new QPushButton("Ok");
    okButton->setDefault(true);
    okButton->setFixedHeight(30);
    okButton->setFixedWidth(50);

    QPushButton *cancelButton = new QPushButton("Cancel");
    cancelButton->setCheckable(true);
    cancelButton->setAutoDefault(false);
    cancelButton->setFixedHeight(30);
    cancelButton->setFixedWidth(50);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(Qt::Horizontal);
    buttonBox->addButton(okButton, QDialogButtonBox::AcceptRole);
    buttonBox->addButton(cancelButton, QDialogButtonBox::RejectRole);

    //QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(buttonBox);

    QObject::connect(buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    if(dialog.exec() == QDialog::Accepted)
    {
        try
        {
            *value = std::stod(line.get()->text().toStdString());
        }
        catch(std::exception e)
        {
            //std::cerr << e.what() << std::endl;
            *mok = false;
            return;
        }
        typeIdx = box.currentIndex();
        type = box.itemText(typeIdx).toStdString();
        //std::cout << *value << " " << typeIdx << std::endl;
        *mok = true;
    }
    else *mok = false;

}

void GuiInput::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    MPEvent = event;
    emit sigBlockClick();
    if(event->button() == Qt::LeftButton)
    {
        Debug::Gui("Left button on input!");
    }
    else if(event->button() == Qt::RightButton)
    {
        Debug::Gui("Right button on input!");
    }
}

void GuiInput::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        // show input value dialog
        getUserValue(&mvalue.value, mvalue.type, &mok);
        mvalue.valid = true;
        emit sigValueChanged();
        //std::cout << mvalue.value << " " << mvalue.type << std::endl;

        setToolTip(QString::fromStdString("Value: "+std::to_string(mvalue.value)+"\nType: "+mvalue.type));
    }
}

void GuiInput::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {}
void GuiInput::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {}

void GuiInput::paint(QPainter *p, const QStyleOptionGraphicsItem *s, QWidget *w)
{
  QGraphicsEllipseItem::paint(p,s,w);
}

QPointF GuiInput::getConnectorPoint(int connector)
{
    QPointF itemPoint = positionCenter;
    QPointF connectorPoint;

    connectorPoint.setX(itemPoint.x() + mradius/2);
    connectorPoint.setY(itemPoint.y());

    return connectorPoint;
}

void GuiInput::getPointFromBlock(int *connector, bool *wireFree)
{
    *connector = -1;
    *wireFree = !output1;
}

void GuiInput::setConnectorAvailability(int connector, bool addWire)
{
    if(addWire) output1 = true;
    else output1 = false;
}
