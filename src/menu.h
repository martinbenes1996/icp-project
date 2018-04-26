#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <map>
#include <string>

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
   
    public slots:
        void slotChoicePressed(QString);
        void slotChoiceRejected();

        void slotLoad() { std::cerr << "Load a scheme.\n"; }
        void slotSave() { std::cerr << "Save the scheme.\n"; }
        void slotExit() { exit(0); }
    signals:
        void sigChoiceMode(long);
        void sigWireMode();
    private:
        QSignalMapper mmapper;
        std::map<QString, QPushButton*> mButtons;
        QVBoxLayout* mlayout;
};

#endif // MENU_H