#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <QWidget>

#include <QPaintEvent>

#include <vector>

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
    
    private:
        bool mchoice = false;
        std::vector<QPointF> mpoints;

};

#endif // PLAYGROUND_H