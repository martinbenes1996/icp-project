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

        void nextResult()
        {
            if(mblockresults.size() <= mblockit)
                throw MyError("Simulation end!", ErrorType::NotAnError);

            if(mblockresults.at(mblockit).second.level != mlastlevel)
            {
                sendWireResults(mlastlevel);
                mlastlevel = mblockresults.at(mblockit).second.level;
            }
            else
            {
                emit sigBlockResult(mblockresults.at(mblockit).first,
                                    mblockresults.at(mblockit).second);
                mblockit++;
            }
        }

        void prevResult()
        {
            if(mblockit == 0) return;
            else
            {
                size_t mendit = mblockit;
                mblockit = 0;
                mlastlevel = 0;
                // reset view
                for(mblockit = 0; mblockit < mendit; mblockit++)
                { 
                    nextResult();
                }
            }
        }

    signals:
        void sigBlockResult(long id, Result);
        void sigWireResult(long id, Result);
    private:
        Model m;
        Window w;

        int mlastlevel = 0;
        std::map<int,std::map<long,Result>> mwireresults;
        std::vector<std::pair<long,Result>> mblockresults;
        size_t mblockit;

        void sendWireResults(int level)
        {
            for(auto& it: mwireresults.at(level))
            {
                emit sigWireResult(it.first, it.second);
            }
        }

};

#endif // CONTROLLER_H
