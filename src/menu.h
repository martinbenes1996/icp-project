#ifndef MENU_H
#define MENU_H

#include <map>
#include <string>

#include <QPushButton>
#include <QSignalMapper>
#include <QString>
#include <QWidget>

class Menu: public QWidget
{
    Q_OBJECT
    public:
        Menu(QWidget* parent = 0);
   
    public slots:
        void slotChoicePressed(QString);
        void slotChoiceRejected();
    signals:
        void sigChoiceMode(long);
    private:
        QSignalMapper mmapper;
        std::map<QString, QPushButton*> mButtons;
};

#endif // MENU_H