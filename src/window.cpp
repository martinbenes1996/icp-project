// window.cpp
// Autoři: xbenes49, xpolan09
// Projekt do předmětu ICP.
// Datum: 29.04.5018


#include <QFileDialog>
#include <QInputDialog>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QSplitter>
#include <QList>        // list of sizes for splitter

#include "debug.h"
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
    QObject::connect(mmenu.get(), SIGNAL(sigInput()), mplayground.get(), SLOT(slotInput()));

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
    QMenu *menu1 = new QMenu(QString("File"), this);
    // new
    QAction *newAction = menu1->addAction(QString("New"));
    newAction->setShortcuts(QKeySequence::New);
    QObject::connect(newAction, SIGNAL(triggered()), this, SLOT(slotNew()) );
    // load
    QAction *loadAction = menu1->addAction(QString("Open"));
    loadAction->setShortcuts(QKeySequence::Open);
    QObject::connect(loadAction, SIGNAL(triggered()), this, SLOT(slotOpen()) );
    // save
    QAction *saveAction = menu1->addAction(QString("Save"));
    saveAction->setShortcuts(QKeySequence::Save);
    QObject::connect(saveAction, SIGNAL(triggered()), this, SLOT(slotSave()) );
    // exit
    QAction *exitAction = menu1->addAction(QString("Exit"));
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setShortcuts(QKeySequence::Close);
    QObject::connect(exitAction, SIGNAL(triggered()), this, SLOT(slotExit()) );
    menubar->addMenu(menu1);

    // create file
    QMenu *menu2 = new QMenu(QString("Run"), this);
    // calculate
    QAction *calculateAction = menu2->addAction(QString("Calculate"));
    QObject::connect(calculateAction, SIGNAL(triggered()), this, SLOT(slotCalculate()) );
    // debug
    QAction *debugAction = menu2->addAction(QString("Debug"));
    debugAction->setShortcuts(QKeySequence::Open);
    QObject::connect(debugAction, SIGNAL(triggered()), this, SLOT(slotDebug()) );
    menubar->addMenu(menu2);

    // create types
    QMenu *menu3 = new QMenu(QString("Types"), this);
    QAction *addTypeAction = menu3->addAction(QString("Add type"));
    QObject::connect(addTypeAction, SIGNAL(triggered()), this, SLOT(slotAddType()));
    QAction *removeTypeAction = menu3->addAction(QString("Remove type"));
    QObject::connect(removeTypeAction, SIGNAL(triggered()), this, SLOT(slotRemoveType()));
    menubar->addMenu(menu3);

    // create help
    QMenu *menu4 = new QMenu(QString("Help"), this);
    QAction *helpAction = menu4->addAction(QString("ShowHelp"));
    menubar->addMenu(menu4);

    QWidget *content = new QWidget(this);
    vlayout->addWidget(content);

    QHBoxLayout *hlayout = new QHBoxLayout(content);
    //hlayout->setContentsMargins(0,0,0,0);
    //hlayout->setSpacing(0);
    hlayout->addWidget(splitter);

    QObject::connect(this, SIGNAL(sigRun(bool)), mmenu.get(), SLOT(slotRun(bool)));

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

void Window::slotDebug() 
{ 
    Debug::Compute("Start debug.");
    mcompute = true;
    emit sigRun(true);
}
void Window::slotCalculate() 
{ 
    Debug::Compute("Start calculate.");
    mcompute = true; 
    emit sigRun(false); 
}

void Window::slotAddType()
{
    bool ok;
    QString val = QInputDialog::getText(0, "Add type",
                "Add type:", QLineEdit::Normal, "", &ok);
    if(!ok) return;

    Config::addType(val.toStdString());
}

void Window::slotRemoveType()
{
    QStringList items;
    for(auto& it: Config::getTypes()) { items << QString::fromStdString(it); }

    bool ok;
    QString val = QInputDialog::getItem(0, "Remove type", "Remove type:", 
                items, 0, true, &ok);
    if(!ok) return;

    Config::removeType(val.toStdString());
}

void Window::slotRemoveType(const QString&)
{

}

void Window::keyPressEvent(QKeyEvent *event)
{
    if(mcompute)
    {
        if(event->key() == Qt::Key_Escape)
        {
            endComputation();
        }
        else if(event->key() == Qt::Key_A)
        {
            Debug::Compute("Previous step.");
            emit sigPreviousResult();
        }
        else if(event->key() == Qt::Key_D)
        {
            Debug::Compute("Next step.");
            emit sigNextResult();
        }
    }
    
}

void Window::endComputation()
{
    Debug::Compute("End computation.");
    mcompute = false;
    mmenu->endComputation();
    mplayground->setAllDefaultColor();
}