
#include <QHBoxLayout>

#include "window.h"

Window::Window(QWidget *parent): QWidget(parent)
{
    resize(320, 240);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);

    mmenu = new Menu(this);
    mplayground = new QWidget(this);

    
    layout->addWidget(mmenu);
    layout->addWidget(mplayground);

    setLayout(layout);

}