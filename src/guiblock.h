#ifndef GUIBLOCK_H
#define GUIBLOCK_H

#include <QWidget>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
//#include <QPointF>
//#include <QRectF>

class GuiBlock: public QWidget//QGraphicsItem
{
  public:
    GuiBlock(int x, int y/*, QGraphicsItem* g = 0*/);

    //QRectF boundingRect() const override;
    void paint(/*QPainter *, const QStyleOptionGraphicsItem *, QWidget **/);

    void paintEvent(/*QPaintEvent**/);
    void mousePressEvent(QMouseEvent *event);

  private:
    QRect rectangle;
    QBrush brush;
    QPen pen;
    double mwidth = 30;
    double mheight = 30;
};

#endif // GUIBLOCK_H
