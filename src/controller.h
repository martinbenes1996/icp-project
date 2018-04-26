#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"
#include "window.h"

class Controller
{
    public:
        Controller();

        void startComputation();
    
    private:
        Model m;
        Window w;
};

#endif // CONTROLLER_H