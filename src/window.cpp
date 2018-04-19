
#include <QHBoxLayout>
#include <QSplitter>

#include "window.h"

Window::Window(QWidget *parent): QWidget(parent)
{
    mmenu = std::make_shared<Menu>(this);
    mplayground = std::make_shared<PlayGround>(this);

    resize(800, 600);

    QObject::connect(mplayground.get(), SIGNAL(sigChoiceRejected()), mmenu.get(), SLOT(slotChoiceRejected()));
    QObject::connect(mmenu.get(), SIGNAL(sigChoiceMode(long)), mplayground.get(), SLOT(slotTypeChoice(long)));

    QSplitter *splitter = new QSplitter(this);
    splitter->addWidget(mmenu.get());
    splitter->addWidget(mplayground->mview);
    splitter->setChildrenCollapsible(false);

    //layout->addWidget(mmenu);
    //layout->addWidget(mplayground);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(splitter);
    setLayout(layout);

}
