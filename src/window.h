#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <memory>

#include <QWidget>

#include "menu.h"
#include "playground.h"

class Window: public QWidget
{
    public:
        Window(QWidget *parent = 0);

        const PlayGround* getPG() const { return mplayground.get(); }
    private:
        std::shared_ptr<PlayGround> mplayground;
        std::shared_ptr<Menu> mmenu;
};

#endif // WINDOW_H