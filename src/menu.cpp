
#include <iostream>
#include <vector>

#include <QVBoxLayout>
#include <QString>

#include "config.h"
#include "defs.h"
#include "menu.h"

Menu::Menu(QWidget* parent): QWidget(parent)
{
    std::vector<std::string> names = Config::getBlockNames();
    QVBoxLayout * layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);

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

    QObject::connect(&mmapper, SIGNAL(mapped(QString)), this, SLOT(slotChoicePressed(QString)));
    setLayout(layout);
}

void Menu::slotChoicePressed(QString name)
{
    emit sigChoiceMode(mButtons.at(name)->isChecked());
    for(auto& it: mButtons) { if(it.first != name) it.second->setChecked(false); }
    // std::cout << name.toStdString() << "\n";
}

void Menu::slotChoiceRejected()
{
    for(auto& it: mButtons) { it.second->setChecked(false); }

}