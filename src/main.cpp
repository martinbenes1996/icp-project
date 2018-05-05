// main.cpp
// Autoři: xbenes49, xpolan09
// Projekt do předmětu ICP.
// Datum: 29.04.5018


#include <iostream>

#include <QApplication>
#include <QPushButton>

#include "config.h"
#include "controller.h"

void setAppStyle(QApplication& app)
{
    QFile File( QString::fromStdString(Config::getStyleFileName()) );
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    app.setStyleSheet(StyleSheet);
}

int main(int argc, char *argv[])
{
    // init config
    Config::initConfig();

    // init qapp
    QApplication app (argc, argv);
    setAppStyle(app);

    // init model
    Controller c;

    // run
    return app.exec();
}


