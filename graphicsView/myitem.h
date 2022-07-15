#ifndef MYITEM_H
#define MYITEM_H

#include <QGraphicsPolygonItem>

const double PI = 4.0 * atan(1.0);

class myItem : public QGraphicsPolygonItem
{
public:
    myItem();
    virtual ~myItem() {};
    virtual void reSetShape(QList<QPointF>* points, int index, double rotate) = 0;
    void refresh(QList<QPointF> *points);
};

#endif // MYITEM_H
