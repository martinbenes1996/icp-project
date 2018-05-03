// controller.cpp
// Autoři: xbenes49, xpolan09
// Projekt do předmětu ICP.
// Datum: 29.04.5018


#include <iostream>
#include <fstream>
#include <cassert>

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
    qRegisterMetaType<Value>("Value");
    QObject::connect(w.getPG(), SIGNAL(sigCreateInput(Value, long&)), &m, SLOT(slotCreateInput(Value, long&)), Qt::DirectConnection);
    QObject::connect(w.getPG(), SIGNAL(sigInputValueChanged(long,Value)), &m, SLOT(slotInputValueChanged(long,Value)));

    QObject::connect(&m, SIGNAL(sigDeleteWire(long)), w.getPG(), SLOT(slotDeleteWire(long)), Qt::DirectConnection);

    QObject::connect(&w, SIGNAL(sigReset()), &m, SLOT(slotReset()));
    QObject::connect(&w, SIGNAL(sigOpen(std::string)), this, SLOT(slotOpen(std::string)));
    QObject::connect(&w, SIGNAL(sigSave(std::string)), this, SLOT(slotSave(std::string)));
    QObject::connect(&w, SIGNAL(sigRun(bool)), this, SLOT(slotRun(bool)));
    QObject::connect(&w, SIGNAL(sigPreviousResult()), this, SLOT(slotPreviousResult()));
    QObject::connect(&w, SIGNAL(sigNextResult()), this, SLOT(slotNextResult()));
    w.show();
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
    Debug::Controller("Controller::slotOpen");
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
    Debug::Controller("Controller::slotSave");
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

void Controller::slotRun(bool debug)
{
    Debug::Controller("Controller::slotRun(dbg="
                     + std::string(((debug)?"true":"false"))
                     + ")" );
    // compute
    SimulationResults results = m.startComputation();
    std::vector<std::pair<long, Result>> r;
    for(auto& i: results.blocks)
    {
        for(auto& j: i.second)
        {
            std::cerr << "id " << j.first << " level " << i.first << "\n";
            assert(i.first == j.second.level);
            r.push_back( std::make_pair(j.first,j.second) );
        }
    }
    mblockresults = r;
    mwireresults = results.wires;
    mlastlevel = 0;
    mblockit = 0;

    if(!debug)
    {
        while(mblockresults.size() > mblockit)
        {
            slotNextResult();
        }
        w.endComputation();
    }
        
}

void Controller::slotPreviousResult()
{
    if(mblockit == 0) return;
    else {
        size_t mendit = mblockit;
        mblockit = 0;
        mlastlevel = 0;
        // reset view
        w.getPG()->setAllDefaultColor();
        while(mblockit < mendit)
        { 
            slotNextResult();
        }
        mblockit--;
        Debug::Compute("slotPreviousResult() = " + std::to_string(mblockit));
    }
}

void Controller::slotNextResult()
{
    if(mblockresults.size() <= mblockit) return;

    if(mblockresults.at(mblockit).second.level != mlastlevel)
    {
        sendWireResults(mlastlevel);
        mlastlevel = mblockresults.at(mblockit).second.level;
    }
    else
    {
        long id = mblockresults.at(mblockit).first;
        Value v = (Value)mblockresults.at(mblockit).second;
        std::cerr << id << ":" << v.value << " " << v.type << " " << v.valid << "\n";
        w.getPG()->setBlockValue(id, v);
        w.getPG()->setBlockColor(id, true);
        mblockit++;
    }
}

void Controller::sendWireResults(int level)
{
    if(mwireresults.count(level) == 0) return;
    for(auto& it: mwireresults.at(level))
    {
        long id = it.first;
        Value v = (Value)it.second;
        w.getPG()->setWireValue(id, v);
        w.getPG()->setWireColor(id, true);
    }
}