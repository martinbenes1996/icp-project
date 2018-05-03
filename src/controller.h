// controller.h
// Autoři: xbenes49, xpolan09
// Projekt do předmětu ICP.
// Datum: 29.04.5018


#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "model.h"
#include "window.h"

/**
 * @brief   This class holds the model and window, connects them together.
 *          It saves and loads from file. It leads the calculations.
 */
class Controller: public QObject
{
    Q_OBJECT
    public:
        /** 
         * @brief   Controller constructor. Connects the model and the window.
         */ 
        Controller();

    public slots:
        /**
         * @brief   Opens the file and loads the data to the model and window.
         *          Called from the 
         * @param path      Path to the file.
         */
        void slotOpen(std::string);
        void slotSave(std::string);
        void slotRun(bool);

        void slotNextResult();
        void slotPreviousResult();
        
    private:
        Model m;
        Window w;

        int mlastlevel = 0;
        std::map<int,std::map<long,Result>> mwireresults;
        std::vector<std::pair<long,Result>> mblockresults;
        size_t mblockit;

        void sendWireResults(int level);

};

#endif // CONTROLLER_H
