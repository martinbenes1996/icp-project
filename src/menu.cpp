
#include <iostream>
#include <map>
#include <vector>

#include <QVBoxLayout>
#include <QString>

#include "config.h"
#include "defs.h"
#include "menu.h"

void Menu::createButton(QString s, bool checkable = true)
{
    // create button
    QPushButton* btn = new QPushButton(this);
    btn->setText(s);
    btn->setCheckable(checkable);
    mButtons.insert( std::make_pair(s, btn) );

    // get to scene
    mlayout->addWidget(btn);

    // map signals
    mmapper.setMapping(btn, s);
    QObject::connect(btn, SIGNAL(pressed()), &mmapper, SLOT(map()));
}

constexpr auto loadBtn = "Load";
constexpr auto saveBtn = "Save";
constexpr auto exitBtn = "Exit";
constexpr auto wireBtn = "Wire";

Menu::Menu(QWidget* parent): QWidget(parent)
{
    mlayout = new QVBoxLayout(this);
    mlayout->setAlignment(Qt::AlignTop);

    // load & save
    createButton(loadBtn, false);
    createButton(saveBtn, false);
    createButton(exitBtn, false);

    QSpacerItem* s1 = new QSpacerItem(1,20);
    mlayout->addSpacerItem(s1);

    // blocks
    auto& names = Config::getBlockNames();
    for(auto& it: names)
    {
        QString s = QString::fromStdString(it.first);
        createButton(s);
    }

    QSpacerItem* s2 = new QSpacerItem(1,20);
    mlayout->addSpacerItem(s2);

    // wire
    createButton(wireBtn);

    QObject::connect(&mmapper, SIGNAL(mapped(QString)), this, SLOT(slotChoicePressed(QString)));
    setLayout(mlayout);
}

void Menu::slotChoicePressed(QString name)
{

    if(name == loadBtn) { slotLoad(); return; }
    else if(name == saveBtn) { slotSave(); return; }
    else if(name == exitBtn) { slotExit(); return; }
    
    for(auto& it: mButtons) { if(it.first != name) it.second->setChecked(false); }
    if(name == wireBtn) { emit sigWireMode(); return; }

    auto m = Config::getBlockNames();
    #warning wtf logic?
    long key = (!mButtons.at(name)->isChecked()) ?
                    m.at(name.toStdString()) : -1;
    emit sigChoiceMode(key);

    // std::cout << name.toStdString() << "\n";
}

void Menu::slotChoiceRejected()
{
    for(auto& it: mButtons) { it.second->setChecked(false); }
}