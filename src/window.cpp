// window.cpp
// Autoři: xbenes49, xpolan09
// Projekt do předmětu ICP.
// Datum: 29.04.5018


#include <QFileDialog>
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
    setContentsMargins(0,0,0,0);

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
    vlayout->setContentsMargins(0,0,0,0);
    vlayout->setSpacing(0);
    setLayout(vlayout);

    // create file
    QMenu *menu1 = new QMenu(QString("Soubor"), this);
    // new
    QAction *newAction = menu1->addAction(QString("Nový"));
    newAction->setShortcuts(QKeySequence::New);
    newAction->setStatusTip( QString("Obnoví program do stavu po spuštění.") );
    QObject::connect(newAction, SIGNAL(triggered()), this, SLOT(slotNew()) );
    // load
    QAction *loadAction = menu1->addAction(QString("Otevřít"));
    loadAction->setShortcuts(QKeySequence::Open);
    loadAction->setStatusTip( QString("Otevře soubor.") );
    QObject::connect(loadAction, SIGNAL(triggered()), this, SLOT(slotOpen()) );
    // save
    QAction *saveAction = menu1->addAction(QString("Uložit"));
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip( QString("Uloží do souboru.") );
    QObject::connect(saveAction, SIGNAL(triggered()), this, SLOT(slotSave()) );
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
    //hlayout->setContentsMargins(0,0,0,0);
    //hlayout->setSpacing(0);
    hlayout->addWidget(splitter);

}

GuiState Window::getState()
{
    GuiState s;
    s.blocks = mplayground->getBlockState();
    return s;
}

void Window::setState(GuiState s)
{
    // blocks
    mplayground->setBlockState(s.blocks);

    // wires
}

void Window::slotOpen()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open file", "", "Block scheme (*.bsc);;All Files (*)");
    emit sigOpen(filename.toStdString());
}

void Window::slotSave()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save file", ".bsc", "Block scheme (*.bsc);;All Files (*)");
    emit sigSave(filename.toStdString());
}


