#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <map>
#include <vector>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include <QPaintEvent>
#include <QVBoxLayout>

#include "config.h"
#include "defs.h"
#include "guiblock.h"

class PlayGround: public QWidget
{
    Q_OBJECT
    public:
        PlayGround(QWidget* parent = 0);

        void mouseMoveEvent(QMouseEvent *event);
        void mousePressEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);

        void paintEvent(QPaintEvent*);

    public slots:
        void slotChoiceMode(bool);
    signals:
        void sigChoiceRejected();

        void sigCreateBlock(BlockType type, long& key);
        void sigDeleteBlock(long key);
        void sigCreateWire(PortID startkey, PortID endkey, long& id);
        void sigDeleteWire(long key);

    private:
        bool mchoice = false;
        std::vector<QPointF> mpoints;

        QGraphicsView *mview = nullptr;
        QGraphicsScene *mscene = nullptr;

        std::map<long, GuiBlock> mBlocks;

};

#endif // PLAYGROUND_H
