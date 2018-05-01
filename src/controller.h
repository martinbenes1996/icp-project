// controller.h
// Autoři: xbenes49, xpolan09
// Projekt do předmětu ICP.
// Datum: 29.04.5018


#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "model.h"
#include "window.h"

class Controller: public QObject
{
    Q_OBJECT
    public:
        Controller();

    public slots:
        void slotOpen(std::string);
        void slotSave(std::string);
        void slotRun(bool);

    private:
        Model m;
        Window w;
};

#endif // CONTROLLER_H
