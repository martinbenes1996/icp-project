
#include <QHBoxLayout>

#include "window.h"

Window::Window(QWidget *parent): QWidget(parent)
{
    resize(800, 600);

    QHBoxLayout *layout = new QHBoxLayout(this);

    mmenu = new Menu(this);
    mplayground = new PlayGround(this);

    QObject::connect(mplayground, SIGNAL(sigChoiceRejected()), mmenu, SLOT(slotChoiceRejected()));
    QObject::connect(mmenu, SIGNAL(sigChoiceMode(bool)), mplayground, SLOT(slotChoiceMode(bool)));
    
    layout->addWidget(mmenu);
    layout->addWidget(mplayground);

    setLayout(layout);

}