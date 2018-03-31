#ifndef VIEW_H
#define VIEW_H

#include <iostream>

#include <QObject>

#include "defs.h"

class View: public QObject
{
    Q_OBJECT

    public slots:
        void slotDeleteWire(long key);
    signals:
        void sigCreateBlock(long type, long& key);
        void sigDeleteBlock(long key);
        void sigCreateWire(PortID startkey, PortID endkey, long& id);
        void sigDeleteWire(long key);

};

#endif // VIEW_H