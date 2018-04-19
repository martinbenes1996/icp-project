
#include <QHBoxLayout>
#include <QSplitter>
#include <QList>        // list of sizes for splitter

#include "window.h"

Window::Window(QWidget *parent): QWidget(parent)
{
    mmenu = std::make_shared<Menu>(this);
    mplayground = std::make_shared<PlayGround>(this);

    resize(800, 600);

    QObject::connect(mplayground.get(), SIGNAL(sigChoiceRejected()), mmenu.get(), SLOT(slotChoiceRejected()));
    QObject::connect(mmenu.get(), SIGNAL(sigChoiceMode(long)), mplayground.get(), SLOT(slotTypeChoice(long)));

    // my very own signals between view and scene
    QObject::connect(mplayground->getPlayGroundView(), SIGNAL(sigViewLeftClick(QMouseEvent *)), mplayground.get(), SLOT(slotViewLeftClick(QMouseEvent *)));
    QObject::connect(mplayground->getPlayGroundView(), SIGNAL(sigViewRightClick(QMouseEvent *)), mplayground.get(), SLOT(slotViewRightClick(QMouseEvent *)));

    // splits the menu part and the playground (view!) part
    QSplitter *splitter = new QSplitter(this);
    splitter->addWidget(mmenu.get());
    splitter->addWidget(mplayground->getPlayGroundView()/*mplayground->mview*/);
    splitter->setChildrenCollapsible(false);        // individual parts cannot disappear

    // Sets starting proportions of splitted parts. Menu should be smaller.
    // Je to zadano v pixelech a proporce to nejak divne dopocitava.
    // Nevim, jak to bude fungovat.
    // Btw jak je to s oblastí platnosti proměnných v konstruktoru... + uvolnovani pameti v qt
    QList<int> splitterList = QList<int>() << 10 << 400;
    splitter->setSizes(splitterList);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(splitter);
    setLayout(layout);

}
