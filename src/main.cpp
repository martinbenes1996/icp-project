/**
 * @file main.h
 * @author xbenes49, xpolan09
 * @date 5 May 2018
 * @brief main module
 *
 * This module contains main.
 */

#include <iostream>

#include <QApplication>
#include <QPushButton>

#include "config.h"
#include "controller.h"

/**
 * @brief Applies the style to the application.
 * @param app       Application.
 */
void setAppStyle(QApplication& app)
{
    QFile File( QString::fromStdString(Config::getStyleFileName()) );
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    app.setStyleSheet(StyleSheet);
}

/**
 * @brief Main function.
 * @param argc      Count of input parameters.
 * @param argv      Input parameters.
 * @returns Exit code.
 */
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


/*! \mainpage BlockEditor 
 * 
 * This app enables to create block schemes, save and load them and do a calculation using them.
 * It is very easy to learn it, and it is a great fun.
 * 
 * \section Controls
 *
 * This application enables to 
 *
 * \section install_sec Installation
 *
 * \subsection step1 Step 1: Opening the box
 *  
 * etc...
 */
