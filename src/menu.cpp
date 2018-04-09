
#include <iostream>
#include <vector>

#include <QVBoxLayout>
#include <QString>

#include "config.h"
#include "menu.h"

Menu::Menu(QWidget* parent): QWidget(parent)
{
    std::vector<std::string> names = Config::getBlockNames();
    QVBoxLayout * layout = new QVBoxLayout(this);

    for(auto& it: names)
    {
        QString s = QString::fromStdString(it);

        // create button
        QPushButton* btn = new QPushButton(this);
        btn->setText(s);
        btn->setCheckable(true);
        mButtons.insert( std::make_pair(s, btn) );

        // get to scene
        layout->addWidget(btn);

        // map signals
        mmapper.setMapping(btn, s);
        QObject::connect(btn, SIGNAL(pressed()), &mmapper, SLOT(map()));
    }
    QObject::connect(&mmapper, SIGNAL(mapped(QString)), this, SLOT(slotPressed(QString)));
    setLayout(layout);
}

void Menu::slotPressed(QString name)
{
    for(auto& it: mButtons) 
    {
        if(it.first != name) it.second->setChecked(false);
        else if(it.second->isChecked()) it.second->setChecked(false);
        #warning WTF logic?
    }
    std::cout << name.toStdString() << "\n";
}