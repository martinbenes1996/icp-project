// main.cpp
// Autoři: xbenes49, xpolan09
// Projekt do předmětu ICP.
// Datum: 29.04.5018


#include <iostream>

#include <QApplication>
#include <QPushButton>

#include "config.h"
#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication app (argc, argv);

    Config::initConfig();
    Controller c;
    //QPushButton button ("Hello world !");
    //button.show();

    return app.exec();
}
