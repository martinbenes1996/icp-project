
#include <QObject>

#include "controller.h"

Controller::Controller()
{
    QObject::connect(&v, SIGNAL(sigCreateBlock(long, long&)), &m, SLOT(slotCreateBlock(long, long&)));
    QObject::connect(&v, SIGNAL(sigDeleteBlock(long)), &m, SLOT(slotDeleteBlock(long)));
    QObject::connect(&v, SIGNAL(sigCreateWire(long, long, long&)), &m, SLOT(slotCreateWire(long, long, long&)));
    QObject::connect(&v, SIGNAL(sigDeleteWire(long)), &m, SLOT(slotDeleteWire(long)));

    QObject::connect(&m, SIGNAL(sigDeleteWire(long)), &v, SLOT(slotDeleteWire(long)));
}