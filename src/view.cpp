
#include <QFile>
#include <QFormBuilder>

#include "view.h"

View::View()
{
    PlayGround* pg = mwin.getPlayGround();
    QObject::connect(pg,SIGNAL(sigCreateBlock(BlockType,long&)),this,SIGNAL(sigCreateBlock(BlockType,long&)), Qt::DirectConnection);
    QObject::connect(pg,SIGNAL(sigDeleteBlock(long)),this,SIGNAL(sigDeleteBlock(long)));
    QObject::connect(pg,SIGNAL(sigCreateWire(PortID,PortID,long&)),this,SIGNAL(sigCreateWire(PortID,PortID,long&)), Qt::DirectConnection);
    QObject::connect(pg,SIGNAL(sigDeleteWire(long)),this,SIGNAL(sigDeleteWire(long)));
    
    mwin.show();
}

void View::slotDeleteWire(long key)
{
    (void)key;
}