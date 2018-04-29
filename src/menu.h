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
   
    public slots:
        void slotChoicePressed(QString);
        void slotChoiceRejected();

    signals:
        void sigChoiceMode(long);
        void sigWireMode();
    private:
        QSignalMapper mmapper;
        std::map<QString, QPushButton*> mButtons;
        QVBoxLayout* mlayout;
        QGridLayout* mblocklayout;
        int mblockiterator = 0;
};

#endif // MENU_H