#include <iostream>

#include <QMouseEvent>
#include <QPainter>

#include "playground.h"

// prehodit mosepressevent do sceny -> oprava view
// guiblock subclasses podle poctu vstupu a vystupu

PlayGround::PlayGround(QWidget* parent): QWidget(parent)
{
  mscene = new QGraphicsScene(this);
  mview = new PlayGroundView(this);
  mview->setScene(mscene);

  mview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  mview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  // (0;0) coordinates are in the top left corner (hopefully)
  // scene is 3000*3000 pixels big. Hopefully it is enough.
  mscene->setSceneRect(0, 0, 3000, 3000);
  mview->setAlignment(Qt::AlignLeft | Qt::AlignTop);
  //mview->setTransformationAnchor(QGraphicsView::AnchorViewCenter);

  //mview->setDragMode(QGraphicsView::ScrollHandDrag);

  QVBoxLayout *layout = new QVBoxLayout();
  layout->addWidget(mview);


  // connects mapper to playground: block -> playground communication
  QObject::connect(&mmapper, SIGNAL(mapped(int)),
                   this, SLOT(slotBlockClick(int)));
}

void PlayGround::slotViewLeftClick(QMouseEvent *event)
{
    //std::cout << event->x() << " PG " << event->y() << std::endl;

    // pro kazdy button doplnit reakci
    if(mchoice != -1)
    {

        // pozadat guiblock o block
        std::shared_ptr<GuiBlock> newBlock = std::make_shared<GuiBlock>(event->pos());
        mscene->addItem(newBlock.get());

        // kolize
        // nejdrive se vlozi blok do sceny a pak se zkontroluje, jestli neni kolize
        // moc se mi to reseni nelibi, mozno udelat bez vkladani?
        QList<QGraphicsItem *> tempList;
        tempList = newBlock->collidingItems();
        if(tempList.empty() != true)
        {
            mscene->removeItem(newBlock.get());
            return;
        }

        // poslat zadost o id modelu
        long id; /**< Tady budes mit to id z modelu */
        emit sigCreateBlock(mchoice, id);
        std::cerr << "blockid: " << id << "\n";

        // map signals
        mmapper.setMapping(newBlock.get(), id);
        QObject::connect(newBlock.get(), SIGNAL(sigBlockClick()),
                         &mmapper, SLOT(map()));

        //rect = mscene->addRect(newBlock);
        //rect->setFlag(QGraphicsItem::ItemIsMovable);

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

void PlayGround::slotBlockClick(int i)
{
    QGraphicsSceneMouseEvent * event;
    std::shared_ptr<GuiBlock> block = mBlocks[i];
    event = block->getMouseEvent();

    if(event->button() == Qt::LeftButton)
    {
        std::cout << "PlayGround: received left click from block: " << i << std::endl;
    }
    else if(event->button() == Qt::RightButton) // delete block
    {
        std::cout << "PlayGround: received right click from block -> deleting block: " << i << std::endl;
        emit sigDeleteBlock(i);     // mapper mi neumoznuje posilat long, jen int
        mscene->removeItem(block.get());
        mBlocks.erase(i);
    }
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

    //std::cout << event->x() << std::endl;
    //std::cout << (QGraphicsSceneMouseEvent *)event->x() << std::endl;
//std::cout << event->x() << " PGV " << event->y() << std::endl;
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

    QGraphicsView::mousePressEvent(event);

}
