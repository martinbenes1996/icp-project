
#include <QHBoxLayout>
#include <QSplitter>

#include "window.h"

Window::Window(QWidget *parent): QWidget(parent)
{
    resize(800, 600);

    QHBoxLayout *layout = new QHBoxLayout(this);

    QSplitter *splitter = new QSplitter(this);

    mmenu = new Menu(this);
    mplayground = new PlayGround(this);

    QObject::connect(mplayground, SIGNAL(sigChoiceRejected()), mmenu, SLOT(slotChoiceRejected()));
    QObject::connect(mmenu, SIGNAL(sigChoiceMode(bool)), mplayground, SLOT(slotChoiceMode(bool)));

    splitter->addWidget(mmenu);
    splitter->addWidget(mplayground);

    //layout->addWidget(mmenu);
    //layout->addWidget(mplayground);
    layout->addWidget(splitter);

    setLayout(layout);

}
