#include <iostream>

#include <QMouseEvent>
#include <QPainter>

#include "playground.h"

// prehodit mosepressevent do sceny -> oprava view
// guiblock subclasses podle poctu vstupu a vystupu
template<class T>
void printNOISOMap(T a)
{
    for(auto i:a)
    {
        std::cout << "map: " << i.first << " " << i.second << std::endl;
    }
}



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

  QVBoxLayout *layout = new QVBoxLayout();
  layout->addWidget(mview);


  // connects mapper to playground: block -> playground communication
  QObject::connect(&mmapper, SIGNAL(mapped(int)),
                   this, SLOT(slotBlockClick(int)));
  // connects wire to playground
  //QObject::connect(&mmapperWire, SIGNAL(mapped(int)),
  //                 this, SLOT(slotWireClick(int)));
}

void PlayGround::slotViewLeftClick(QMouseEvent *event)
{
    //std::cout << event->x() << " PG " << event->y() << std::endl;

    // pro kazdy button doplnit reakci
    if(mchoice >= 0 || mchoice <= 2)
    {

        // pozadat guiblock o block
        std::shared_ptr<GuiBlock> newBlock = std::make_shared<GuiBlock>(event->pos(), mchoice);
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

    // for testing a loop detection
    //long id;
    //emit sigCreateWire({0,-1}, {1,0}, id);
    //emit sigCreateWire({1,-1}, {0,0}, id);

    //std::cout << "PG: Accepted signal right click\n";
}

long PlayGround::getIDFromBlock(std::shared_ptr<GuiBlock> block)
{
    for(auto i: mBlocks)
    {
        if(i.second == block) return i.first;
    }
    return -1;
}

bool PlayGround::createWireFunction()
{
    // wire request
    long id;
    bool success = true;
    emit sigCreateWire({getIDFromBlock(block1),connector1}, {getIDFromBlock(block2),connector2}, id, success);
    if(!success) return false;

    // put wire into map
    QPointF point1 = block1.get()->getConnectorPoint(connector1);
    QPointF point2 = block2.get()->getConnectorPoint(connector2);
    std::shared_ptr<MyWire> newWire = std::make_shared<MyWire>(point1, point2);
    mWires.insert( std::make_pair(id,newWire) );
    // draw wire
    mscene->addItem(newWire->getLine());
    // connectiong wire (line) to playground
    //mmapperWire.setMapping(newWire.get(), id);
    //QObject::connect(newWire.get(), SIGNAL(sigWireClick()),
    //                 &mmapperWire, SLOT(map()));

    return true;
}

void PlayGround::deleteWireFunction(long i)
{
    std::cout << "PlayGround: deleting wire: " << i << std::endl;
    emit sigDeleteWire(i);     // mapper mi neumoznuje posilat long, jen int
    std::shared_ptr<MyWire> wire = mWires[i];

    mscene->removeItem(wire.get()->getLine());
    mWires.erase(i);
}

void PlayGround::slotDeleteWire(long i)
{
    deleteWireFunction(i);
}

void PlayGround::slotBlockClick(int i)
{
    QGraphicsSceneMouseEvent * event;
    std::shared_ptr<GuiBlock> block = mBlocks[i];
    event = block->getMouseEvent();

    if(event->button() == Qt::LeftButton)
    {
        std::cout << "PlayGround: received left click from block: " << i << std::endl;

        // wire selected ...
        if(mchoice == 3)
        {
            bool wireFree;
            int connector;

            block->getPointFromBlock(&connector, &wireFree);
            if(block1.get() == nullptr)
            {
                block1 = block;
                connector1 = connector;
                createWire = createWire || wireFree;
            }
            else
            {
                block2 = block;
                connector2 = connector;
                createWire = createWire && wireFree;
                if(createWire)
                {
                    if(createWireFunction())
                    {
                        block1->setConnectorAvailability(connector1, true);
                        block2->setConnectorAvailability(connector2, true);
                    }
                }
                block1 = nullptr;
                block2 = nullptr;
                createWire = false;
                //printNOISOMap(mWires);
            }
        }
    }
    else if(event->button() == Qt::RightButton) // delete block
    {
        std::cout << "PlayGround: received right click from block -> deleting block: " << i << std::endl;
        emit sigDeleteBlock(i);     // mapper mi neumoznuje posilat long, jen int
        mscene->removeItem(block.get());
        mBlocks.erase(i);
    }
}
/*
void PlayGround::slotWireClick(int i)
{
    std::cout << "wire clicked\n";
}
*/

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
