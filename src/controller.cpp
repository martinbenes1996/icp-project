// controller.cpp
// Autoři: xbenes49, xpolan09
// Projekt do předmětu ICP.
// Datum: 29.04.5018


#include <iostream>
#include <fstream>

#include <QObject>

#include "config.h"
#include "controller.h"
#include "debug.h"
#include "defs.h"

Controller::Controller()
{

    QObject::connect(w.getPG(), SIGNAL(sigCreateBlock(long, long&)), &m, SLOT(slotCreateBlock(long, long&)), Qt::DirectConnection);
    QObject::connect(w.getPG(), SIGNAL(sigDeleteBlock(long)), &m, SLOT(slotDeleteBlock(long)));
    qRegisterMetaType<PortID>("PortID");
    QObject::connect(w.getPG(), SIGNAL(sigCreateWire(PortID, PortID, long&, bool&)), &m, SLOT(slotCreateWire(PortID, PortID, long&, bool&)), Qt::DirectConnection);
    QObject::connect(w.getPG(), SIGNAL(sigDeleteWire(long)), &m, SLOT(slotDeleteWire(long)));

    QObject::connect(&m, SIGNAL(sigDeleteWire(long)), w.getPG(), SLOT(slotDeleteWire(long)), Qt::DirectConnection);

    QObject::connect(&w, SIGNAL(sigReset()), &m, SLOT(slotReset()));
    QObject::connect(&w, SIGNAL(sigOpen(std::string)), this, SLOT(slotOpen(std::string)));
    QObject::connect(&w, SIGNAL(sigSave(std::string)), this, SLOT(slotSave(std::string)));
    w.show();
}

void Controller::startComputation()
{
    m.startComputation();
}

std::vector<std::string> split(std::string s)
{
    std::string delimiter = ",";
    size_t pos = 0;
    std::vector<std::string> v;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        v.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    v.push_back(s);
    return v;
}

void Controller::slotOpen(std::string path)
{
    Debug::Controller("Open!");
    std::filebuf fb;
    fb.open (path,std::ios::in);
    std::istream os(&fb);

    std::string s;
    if(!getline(os,s) || s != "# BLOCKS #") exit(1);

    GuiState gs;
    ModelState ms;

    while( getline(os, s) ) {
        std::vector<std::string> v = split(s);
        if(s == "# WIRES #") break;
        try {
            long id = std::stol(v.at(0));
            long type = std::stol(v.at(1));
            double x = std::stod(v.at(2));
            double y = std::stod(v.at(3));

            GuiBlockDescriptor g;
            g.pos = std::make_pair(x,y);
            g.type = type;

            gs.blocks.insert( std::make_pair(id, g) );
            ms.blocks.insert( std::make_pair(id, type) );
        } catch(std::exception& e) {
            std::cerr << "Invalid input file!\n";
            return;
        }
    }

    // read wires
    w.reinit();
    m.reinit();

    w.setState(gs);
    m.setState(ms);


}

void Controller::slotSave(std::string path)
{
    Debug::Controller("Save!");
    // get states
    GuiState gs = w.getState();
    ModelState ms = m.getState();
    // open file
    std::filebuf fb;
    fb.open (path,std::ios::out);
    std::ostream os(&fb);
    // save blocks
    os << "# BLOCKS #\n";
    for(auto& it: gs.blocks)
    {
        os << it.first << ","
           << ms.blocks.at(it.first) << ","
           << it.second.pos.first << ","
           << it.second.pos.second << "\n";
    }
    // save wires
    os << "# WIRES #\n";

    fb.close();
}
