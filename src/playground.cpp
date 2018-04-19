#include <iostream>

#include <QMouseEvent>
#include <QPainter>

#include "playground.h"

PlayGround::PlayGround(QWidget* parent): QWidget(parent)
{
  mscene = new QGraphicsScene(this);
  mview = new PlayGroundView(this);
  mview->mview->setScene(mscene);
  //mview = new QGraphicsView(this);
  layout = new QVBoxLayout();

  //mview->setSceneRect(10, 10, 300, 300);
  //mview->setScene(mscene);

  //mview->setAlignment(Qt::AlignLeft | Qt::AlignTop);
  //mview->setDragMode(QGraphicsView::ScrollHandDrag);
  mscene->addEllipse(10, 10, 100, 100);

  //QVBoxLayout *layout = new QVBoxLayout();
  //layout->addWidget(mview);

}

PlayGroundView::PlayGroundView(QWidget* parent): QWidget(parent)
{
  //mscene = new QGraphicsScene(this);
  //par = parent;
  mview = new QGraphicsView(this);
  layout = new QVBoxLayout();


  //mview->setSceneRect(10, 10, 300, 300);
  //mview->setScene(par->mscene);

  mview->setAlignment(Qt::AlignLeft | Qt::AlignTop);
  //mview->setDragMode(QGraphicsView::ScrollHandDrag);
  //mscene->addEllipse(10, 10, 100, 100);

  //QVBoxLayout *layout = new QVBoxLayout();
  layout->addWidget(mview);

}
/*
void PlayGround::mouseMoveEvent(QMouseEvent *event)
{
    (void)event;
    std::cout << "PlayGround::mouseMoveEvent()\n";
}

void PlayGround::mousePressEvent(QMouseEvent *event)
{
    (void)event;
    std::cout << "PlayGround::mousePressEvent()\n";

    //GuiBlock *b = new GuiBlock(event->pos());
    mscene->addRect(event->x(), event->y(), 10, 10);
}

void PlayGround::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton) { emit sigChoiceRejected(); }
    else
    {

        long x = 1;
        // tady to odesle signal do modelu a nahraje to do x
        // id, ktere vygeneruje model ;)
        emit sigCreateBlock(x);
        std::cerr << "playground: " << x << std::endl;

        std::shared_ptr<GuiBlock> b = std::make_shared<GuiBlock>(event->windowPos());
        mscene->addItem(b.get());
        mview->show();

        update();
        //QPointF pos = event->localPos();
        //mpoints.push_back(pos);
        //update();
    }

    //(void)event;
    //std::cout << "PlayGround::mouseReleaseEvent()\n";
}

void PlayGround::paintEvent(QPaintEvent *event)
{
    //QPainter p(this);
    //p.drawLine(10, 10, 1000, 1000);
    //p.setPen(Qt::blue);
    //p.setBrush(Qt::SolidPattern);
    //for(auto& it: mpoints)
    //    p.drawEllipse(it, 5, 5);
}
*/

void PlayGroundView::mousePressEvent(QMouseEvent *event, PlayGround *par)
{
    (void)event;
    std::cout << "PlayGround::mousePressEvent()\n";

    //GuiBlock *b = new GuiBlock(event->pos());
    par->mscene->addRect(event->x(), event->y(), 10, 10);
}
