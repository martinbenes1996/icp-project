
#include <QObject>

#include "controller.h"
#include "defs.h"

Controller::Controller()
{
    QObject::connect(&v, SIGNAL(sigCreateBlock(long, long&)), &m, SLOT(slotCreateBlock(long, long&)));
    QObject::connect(&v, SIGNAL(sigDeleteBlock(long)), &m, SLOT(slotDeleteBlock(long)));
    qRegisterMetaType<PortID>("PortID");    
    QObject::connect(&v, SIGNAL(sigCreateWire(PortID, PortID, long&)), &m, SLOT(slotCreateWire(PortID, PortID, long&)));
    QObject::connect(&v, SIGNAL(sigDeleteWire(long)), &m, SLOT(slotDeleteWire(long)));

    QObject::connect(&m, SIGNAL(sigDeleteWire(long)), &v, SLOT(slotDeleteWire(long)));

}