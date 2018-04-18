#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"
#include "view.h"

class Controller
{
    public:
        Controller();
        //~Controller() {}
    
    private:
        Model m;
        View v;


};

#endif // CONTROLLER_H