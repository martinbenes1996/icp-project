#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>

#include <QWidget>

#include "menu.h"

class Window: public QWidget
{
    public:
        Window(QWidget *parent = 0);
        void test() {
            std::cout << "Playground: " << mplayground << "\n";
            std::cout << "Menu: " << mmenu << "\n";
        }
    private:
        QWidget* mplayground = nullptr;
        Menu* mmenu = nullptr;
};

#endif // WINDOW_H