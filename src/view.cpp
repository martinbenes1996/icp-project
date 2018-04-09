
#include <QFile>
#include <QFormBuilder>

#include "view.h"

View::View()
{
    mwin.show();
}

void View::slotDeleteWire(long key)
{
    (void)key;
}