// window.h
// Autoři: xbenes49, xpolan09
// Projekt do předmětu ICP.
// Datum: 29.04.5018


#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <memory>

#include <QWidget>

#include "menu.h"
#include "playground.h"

struct GuiState {
   std::map<long, GuiBlockDescriptor> blocks;
   // wires
};

class Window: public QWidget
{
    Q_OBJECT
    public:
        Window(QWidget *parent = 0);
        virtual ~Window() {}

        const PlayGround* getPG() const { return mplayground.get(); }

        GuiState getState();
        void setState(GuiState);
        void reinit() { mplayground->reinit(); mmenu->reinit(); }

    public slots:
        void slotExit() { exit(0); }
        void slotNew() { reinit(); emit sigReset(); }
        void slotOpen();
        void slotSave();
        void slotDebug();
        void slotCalculate();
        void slotAddType();
        void slotRemoveType();
        void slotRemoveType(const QString&);
    signals:
        void sigReset();
        void sigOpen(std::string);
        void sigSave(std::string);
        void sigRun(bool dbg);
    private:
        std::shared_ptr<PlayGround> mplayground;
        std::shared_ptr<Menu> mmenu;
};

#endif // WINDOW_H
