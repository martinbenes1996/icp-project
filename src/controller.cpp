
#include <QObject>

#include "controller.h"
#include "defs.h"

Controller::Controller()
{
    qRegisterMetaType<BlockType>("BlockType"); 
    QObject::connect(&v, SIGNAL(sigCreateBlock(BlockType, long&)), &m, SLOT(slotCreateBlock(BlockType, long&)), Qt::DirectConnection);
    QObject::connect(&v, SIGNAL(sigDeleteBlock(long)), &m, SLOT(slotDeleteBlock(long)));
    qRegisterMetaType<PortID>("PortID");    
    QObject::connect(&v, SIGNAL(sigCreateWire(PortID, PortID, long&)), &m, SLOT(slotCreateWire(PortID, PortID, long&)), Qt::DirectConnection);
    QObject::connect(&v, SIGNAL(sigDeleteWire(long)), &m, SLOT(slotDeleteWire(long)));

    QObject::connect(&m, SIGNAL(sigDeleteWire(long)), &v, SLOT(slotDeleteWire(long)));

}