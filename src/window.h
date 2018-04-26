#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <memory>

#include <QWidget>

#include "menu.h"
#include "playground.h"

class Window: public QWidget
{
    Q_OBJECT
    public:
        Window(QWidget *parent = 0);
        virtual ~Window() {}

        const PlayGround* getPG() const { return mplayground.get(); }

    public slots:
        void slotExit() { exit(0); }
        void slotNew() { mplayground->reinit(); emit sigReset(); }
    signals:
        void sigReset();
    private:
        std::shared_ptr<PlayGround> mplayground;
        std::shared_ptr<Menu> mmenu;
};

#endif // WINDOW_H