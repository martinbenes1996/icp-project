
#include <QHBoxLayout>
#include <QMenuBar>
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

    QObject::connect(mmenu.get(), SIGNAL(sigWireMode()), mplayground.get(), SLOT(slotWireMode()));

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

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    QMenuBar *menubar = new QMenuBar(this);
    vlayout->addWidget(menubar);
    setLayout(vlayout);

    // create file
    QMenu *menu1 = new QMenu(QString("Soubor"), this);
    // new
    QAction *newAction = menu1->addAction(QString("Nový"));
    newAction->setShortcuts(QKeySequence::New);
    newAction->setStatusTip( QString("Obnoví program do stavu po spuštění.") );
    QObject::connect(newAction, SIGNAL(triggered()), this, SLOT(slotNew()) );
    // load
    QAction *loadAction = menu1->addAction(QString("Načíst"));
    // save
    QAction *saveAction = menu1->addAction(QString("Uložit"));
    // export
    QAction *exportAction = menu1->addAction(QString("Exportovat"));
    // exit
    QAction *exitAction = menu1->addAction(QString("Ukončit"));
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setShortcuts(QKeySequence::Close);
    exitAction->setStatusTip( QString("Ukončí program a zavře okno.") );
    QObject::connect(exitAction, SIGNAL(triggered()), this, SLOT(slotExit()) );

    menubar->addMenu(menu1);

    // create help
    QMenu *menu2 = new QMenu(QString("Nápověda"), this);
    QAction *helpAction = menu2->addAction(QString("Pomoc"));
    menubar->addMenu(menu2);

    QWidget *content = new QWidget(this);
    vlayout->addWidget(content);

    QHBoxLayout *hlayout = new QHBoxLayout(content);
    hlayout->addWidget(splitter);

}
