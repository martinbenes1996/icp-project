
/**
 * @file controller.h
 * @author xbenes49, xpolan09
 * @date 5 May 2018
 * @brief controller 
 *
 * This module contains a Controller class, that holds the model and the window.
 */

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
         *          Called from the window, where the dialog is raised.
         * @param path      Path to the file.
         */
        void slotOpen(std::string);
        /**
         * @brief   Opens the file and saves the state of the model and window.
         *          Called from the window, where the dialog is raised.
         * @param path      Path to the file.
         */
        void slotSave(std::string);
        /**
         * @brief   Runs the computation
         * @param dbg       Weather to step, or run altogether.
         */
        void slotRun(bool);
        /**
         * @brief   Sends next result in computation.
         */
        void slotNextResult();
        /**
         * @brief   Sends previous result in computation.  
         */
        void slotPreviousResult();
        /**
         * @brief   End computation (from window).
         */
        void slotEndComputation();

    private:
        Model m; /**< Model object. */
        Window w; /**< Window object. */

        /* -------- computation variables ---------- */
        int mlastlevel = 0; /**< Last result level. */
        std::map<int,std::map<long,Result>> mwireresults; /**< Results of wires. */
        std::vector<std::pair<long,Result>> mblockresults; /**< Results of blocks */
        size_t mblockit; /**< Block iterator. */
        /**
         * @brief   Emits all the wires at the given level.
         * @param level     Level of the emitted wires.
         */
        void sendWireResults(int level);
        /* ----------------------------------------- */
};

#endif // CONTROLLER_H
