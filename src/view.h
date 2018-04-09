#ifndef VIEW_H
#define VIEW_H

#include <iostream>

#include <QObject>

#include "config.h"
#include "defs.h"
#include "window.h"

class View: public QObject
{
    Q_OBJECT
    public:
        View();

    public slots:
        void slotDeleteWire(long key);
    signals:
        void sigCreateBlock(BlockType type, long& key);
        void sigDeleteBlock(long key);
        void sigCreateWire(PortID startkey, PortID endkey, long& id);
        void sigDeleteWire(long key);
    
    private:
        Window mwin;

};

#endif // VIEW_H