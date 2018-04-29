
#include <iostream>

#include <QObject>

#include "config.h"
#include "controller.h"
#include "defs.h"

Controller::Controller()
{

    QObject::connect(w.getPG(), SIGNAL(sigCreateBlock(long, long&)), &m, SLOT(slotCreateBlock(long, long&)), Qt::DirectConnection);
    QObject::connect(w.getPG(), SIGNAL(sigDeleteBlock(long)), &m, SLOT(slotDeleteBlock(long)));
    qRegisterMetaType<PortID>("PortID");
    QObject::connect(w.getPG(), SIGNAL(sigCreateWire(PortID, PortID, long&, bool&)), &m, SLOT(slotCreateWire(PortID, PortID, long&, bool&)), Qt::DirectConnection);
    QObject::connect(w.getPG(), SIGNAL(sigDeleteWire(long)), &m, SLOT(slotDeleteWire(long)));

    QObject::connect(&m, SIGNAL(sigDeleteWire(long)), w.getPG(), SLOT(slotDeleteWire(long)));

    QObject::connect(&w, SIGNAL(sigReset()), &m, SLOT(slotReset()));
    QObject::connect(&w, SIGNAL(sigOpen()), this, SLOT(slotOpen()));
    QObject::connect(&w, SIGNAL(sigSave()), this, SLOT(slotSave()));
    w.show();
}

void Controller::startComputation()
{
    m.startComputation();
}

void Controller::slotOpen()
{
    std::cerr << "Open!\n";
}

void Controller::slotSave()
{
    std::cerr << "Save!\n";
    GuiState gs = w.getState();
    ModelState ms = m.getState();
    for(auto& it: gs.blocks) std::cerr << it.first << ": " << it.second.first << "," << it.second.second << "\n";
    for(auto& it: ms.blocks) std::cerr << it.first << ": " << it.second << "\n";
    
}
