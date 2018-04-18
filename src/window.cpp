
#include <QHBoxLayout>
#include <QSplitter>

#include "window.h"

Window::Window(QWidget *parent): QWidget(parent)
{
    resize(800, 600);

    mmenu = new Menu(this);
    mplayground = new PlayGround(this);

    QObject::connect(mplayground, SIGNAL(sigChoiceRejected()), mmenu, SLOT(slotChoiceRejected()));
    QObject::connect(mmenu, SIGNAL(sigChoiceMode(bool)), mplayground, SLOT(slotChoiceMode(bool)));

    QSplitter *splitter = new QSplitter(this);
    splitter->addWidget(mmenu);
    splitter->addWidget(mplayground);
    splitter->setChildrenCollapsible(false);

    //layout->addWidget(mmenu);
    //layout->addWidget(mplayground);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(splitter);
    setLayout(layout);

}
