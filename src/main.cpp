
#include <iostream>

#include <QApplication>
#include <QPushButton>

#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication app (argc, argv);

    Controller c;
    //QPushButton button ("Hello world !");
    //button.show();

    return app.exec();
}