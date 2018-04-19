#include <iostream>

#include <QMouseEvent>
#include <QPainter>

#include "playground.h"

PlayGround::PlayGround(QWidget* parent): QWidget(parent)
{
  mscene = new QGraphicsScene(this);
  mview = new PlayGroundView(this);
  mview->setScene(mscene);

  // (0;0) coordinates are in the top left corner (hopefully)
  mview->setAlignment(Qt::AlignLeft | Qt::AlignTop);

  //mview->setDragMode(QGraphicsView::ScrollHandDrag);

  mscene->addEllipse(10, 10, 100, 100);     // testing elipse, will be removed

  QVBoxLayout *layout = new QVBoxLayout();
  layout->addWidget(mview);

}

void PlayGround::slotViewLeftClick(QMouseEvent *event)
{
    // pro kazdy button doplnit reakci
    if(mchoice != -1)
    {
        // poslat zadost o id modelu
        long id; /**< Tady budes mit to id z modelu */
        emit sigCreateBlock(mchoice, id);
        std::cerr << "blockid: " << id << "\n";

        //QGraphicsRectItem * rect;
        // pozadat guiblock o block
        std::shared_ptr<GuiBlock> newBlock = std::make_shared<GuiBlock>(event->pos());
        mscene->addItem(newBlock.get());
        //rect = mscene->addRect(newBlock);
        //rect->setFlag(QGraphicsItem::ItemIsMovable);

        // hodit to do sceny + kolize

        // a ulozis si to sem:
        mBlocks.insert( std::make_pair(id,newBlock) );
    }
    //std::cout << "PG: Accepted signal left click\n";
}
void PlayGround::slotViewRightClick(QMouseEvent *event)
{
    (void *)event;
    //std::cout << "PG: Accepted signal right click\n";
}

// All of these functions, if needed, will have to be moved to PlayGrounView
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

void PlayGroundView::mousePressEvent(QMouseEvent *event)
{
    //(void)event;
    //std::cout << "PlayGroundView::mousePressEvent()\n";

    if(event->button() == Qt::LeftButton)
    {
        std::cout << "PlayGroundView: sends signal left click\n";
        emit sigViewLeftClick(event);
    }
    else if(event->button() == Qt::RightButton)
    {
        std::cout << "PlayGroundView: sends signal right click\n";
        emit sigViewRightClick(event);
    }

    //GuiBlock *b = new GuiBlock(event->pos());
    //par->mscene->addRect(event->x(), event->y(), 10, 10);
}
