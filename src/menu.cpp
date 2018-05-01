// menu.cpp
// Autoři: xbenes49, xpolan09
// Projekt do předmětu ICP.
// Datum: 29.04.5018


#include <iostream>
#include <map>
#include <vector>

#include <QVBoxLayout>
#include <QString>

#include "config.h"
#include "defs.h"
#include "menu.h"

void Menu::createImageButton(QString s)
{
    // create button
    QPushButton* btn = new QPushButton(this);

    QPixmap pixmap( QString::fromStdString(Config::getImagePath(s.toStdString())) );
    pixmap = pixmap.scaledToHeight(50);
    QIcon ButtonIcon(pixmap);
    btn->setIcon(ButtonIcon);
    btn->setIconSize(pixmap.rect().size());

    btn->setCheckable(true);
    mButtons.insert( std::make_pair(s, btn) );

    // get to scene
    mblocklayout->addWidget(btn,mblockiterator/2, mblockiterator%2);
    mblockiterator++;

    // map signals
    mmapper.setMapping(btn, s);
    QObject::connect(btn, SIGNAL(pressed()), &mmapper, SLOT(map()));
}

void Menu::createTextButton(QString s, bool checkable = true)
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

constexpr auto compBtn = "Compute";
constexpr auto stepBtn = "Step";
constexpr auto wireBtn = "Wire";
constexpr auto inputBtn = "Input";

Menu::Menu(QWidget* parent): QWidget(parent)
{
    mlayout = new QVBoxLayout(this);
    mlayout->setAlignment(Qt::AlignTop);
    mlayout->setContentsMargins(0,0,0,0);
    mlayout->setSpacing(0);

    QWidget * blocksection = new QWidget();
    
    mblocklayout = new QGridLayout(blocksection);
    mblocklayout->setSpacing(0);
    mblocklayout->setContentsMargins(0,0,0,0);
    mlayout->addWidget(blocksection);

    blocksection->setContentsMargins(0,0,0,0);
    blocksection->setLayout(mblocklayout);

    // blocks
    auto& names = Config::getBlockNames();
    for(auto& it: names)
    {
        QString s = QString::fromStdString(it.first);
        createImageButton(s);
    }

    QSpacerItem* s3 = new QSpacerItem(1,20);
    mlayout->addSpacerItem(s3);

    // wire
    createTextButton(wireBtn);
    createTextButton(inputBtn);

    QObject::connect(&mmapper, SIGNAL(mapped(QString)), this, SLOT(slotChoicePressed(QString)));
    setContentsMargins(0,0,0,0);
    setLayout(mlayout);
}

void Menu::slotChoicePressed(QString name)
{

    for(auto& it: mButtons) { if(it.first != name) it.second->setChecked(false); }
    #warning wtf logic?
    if(mButtons.at(name)->isChecked()) { emit sigChoiceMode(-1); return; }
    if(name == wireBtn) { emit sigWireMode(); return; }
    if(name == inputBtn) { emit sigInput(); return; }

    auto m = Config::getBlockNames();
    emit sigChoiceMode(m.at(name.toStdString()));

    // std::cout << name.toStdString() << "\n";
}

void Menu::slotChoiceRejected()
{
    for(auto& it: mButtons) { it.second->setChecked(false); }
}

void Menu::reinit()
{
    for(auto& it: mButtons) { it.second->setChecked(false); }
}
