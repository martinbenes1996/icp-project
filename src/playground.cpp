#include <iostream>

#include <QMouseEvent>
#include <QPainter>

#include "playground.h"

PlayGround::PlayGround(QWidget* parent): QWidget(parent)
{
  mscene = new QGraphicsScene(this);
  mview = new QGraphicsView(this);

  //mview->setSceneRect(10, 10, 300, 300);
  mview->setScene(mscene);

  mview->setAlignment(Qt::AlignLeft | Qt::AlignTop);
  //mview->setDragMode(QGraphicsView::ScrollHandDrag);
  //mscene->addEllipse(10, 10, 100, 100);

  QVBoxLayout *layout = new QVBoxLayout();
  layout->addWidget(mview);

}

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

        long x = 0;
        // tady to odesle signal do modelu a nahraje to do x
        // id, ktere vygeneruje model ;)
        emit sigCreateBlock(BlockType::OneIn_OneOut, x);
        //std::cerr << x << std::endl;

        GuiBlock *b = new GuiBlock(event->windowPos());
        mscene->addItem(b);
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
