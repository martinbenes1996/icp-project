#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <memory>

#include <QWidget>

#include "menu.h"
#include "playground.h"

struct GuiState {
   std::map<long, std::pair<double,double>> blocks;
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
        void reinit() { mplayground->reinit(); mmenu->reinit(); }

    public slots:
        void slotExit() { exit(0); }
        void slotNew() { reinit(); emit sigReset(); }
        void slotOpen() { emit sigOpen(); }
        void slotSave() { emit sigSave(); }
    signals:
        void sigReset();
        void sigOpen();
        void sigSave(); 
    private:
        std::shared_ptr<PlayGround> mplayground;
        std::shared_ptr<Menu> mmenu;
};

#endif // WINDOW_H