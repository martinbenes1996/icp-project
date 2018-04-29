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

        void startComputation();

    public slots:
        void slotOpen();
        void slotSave();

    private:
        Model m;
        Window w;
};

#endif // CONTROLLER_H