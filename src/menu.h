// menu.h
// Autoři: xbenes49, xpolan09
// Projekt do předmětu ICP.
// Datum: 29.04.5018


#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <map>
#include <string>

#include <QGridLayout>
#include <QPushButton>
#include <QSignalMapper>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>

class Menu: public QWidget
{
    Q_OBJECT
    public:
        Menu(QWidget* parent = 0);
        void createImageButton(QString);
        void createTextButton(QString,bool);

        void reinit();

        void endComputation();

    public slots:
        void slotChoicePressed(QString);
        void slotChoiceRejected();
        void slotRun(bool);

    signals:
        void sigChoiceMode(long);
        void sigWireMode();
        void sigInput();

    private:
        QSignalMapper mmapper;
        std::map<QString, QPushButton*> mButtons;
        QVBoxLayout* mlayout;
        QGridLayout* mblocklayout;
        int mblockiterator = 0;
};

#endif // MENU_H
