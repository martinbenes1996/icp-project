#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>

#include <QWidget>

#include "menu.h"
#include "playground.h"

class Window: public QWidget
{
    public:
        Window(QWidget *parent = 0);

        PlayGround* getPlayGround() const { return mplayground; }
    private:
        PlayGround* mplayground = nullptr;
        Menu* mmenu = nullptr;
};

#endif // WINDOW_H